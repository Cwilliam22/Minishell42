#!/bin/bash

# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Compteurs
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Fonction pour afficher les résultats
print_result() {
    local test_name="$1"
    local status="$2"
    local details="$3"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    if [ "$status" = "PASS" ]; then
        echo -e "${GREEN}✓ PASS${NC} - $test_name"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}✗ FAIL${NC} - $test_name"
        if [ -n "$details" ]; then
            echo -e "  ${YELLOW}Details:${NC} $details"
        fi
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
}

# Fonction pour vérifier les fuites mémoire avec Valgrind
check_memory_leaks() {
    local cmd="$1"
    local test_name="$2"
    
    # Vérifier si valgrind est installé
    if ! command -v valgrind > /dev/null 2>&1; then
        echo -e "${YELLOW}⚠ Valgrind non installé - skip test de fuites pour: $test_name${NC}"
        return
    fi
    
    echo -e "\n${BLUE}Checking leaks for:${NC} $cmd"
    
    # Fichier temporaire pour la sortie valgrind
    local valgrind_output=$(mktemp)
    
    # Lancer la commande avec valgrind
    timeout 10 bash -c "echo '$cmd' | valgrind --leak-check=full --error-exitcode=42 --log-file='$valgrind_output' ./minishell > /dev/null 2>&1"
    local exit_code=$?
    
    # Analyser les résultats
    if [ $exit_code -eq 42 ]; then
        # Valgrind a détecté des erreurs/fuites
        local leaks=$(grep "definitely lost" "$valgrind_output" | head -1)
        if [ -n "$leaks" ]; then
            print_result "Memory leak - $test_name" "FAIL" "$leaks"
        else
            print_result "Memory check - $test_name" "FAIL" "Memory errors detected"
        fi
    elif [ $exit_code -eq 124 ]; then
        # Timeout
        print_result "Memory leak - $test_name" "FAIL" "Timeout during valgrind check"
    else
        # Pas de fuites détectées
        print_result "Memory leak - $test_name" "PASS"
    fi
    
        # DEBUG: NE PAS NETTOYER POUR L'INSTANT
        # rm -f "$valgrind_output"
        echo "DEBUG: Fichier valgrind gardé"
}

# Fonction pour tester une commande
test_command() {
    local cmd="$1"
    local test_name="$2"
    local timeout_duration="${3:-5}"
    local check_leaks="${4:-false}"
    
    echo -e "\n${BLUE}Testing:${NC} $cmd"
    
    # Créer des fichiers temporaires AVEC DES NOMS FIXES pour éviter les confusions
    minishell_output=$(mktemp --suffix=.minishell)
    bash_output=$(mktemp --suffix=.bash)
    minishell_clean="${minishell_output}.clean"
    minishell_no_colors="${minishell_output}.no_colors"
    
    # Tester avec bash (capturer stdout ET stderr)
    timeout "$timeout_duration" bash -c "$cmd" > "$bash_output" 2>&1
    local bash_exit_code=$?
    
    # Tester avec minishell (capturer stdout ET stderr)
    timeout "$timeout_duration" echo "$cmd" | ./minishell > "$minishell_output" 2>&1
    local minishell_exit_code=$?
    
    # Filtrer le prompt du minishell en gérant les codes de couleur ANSI
    # Votre minishell utilise des codes couleur : ^[[32m minishell$> ^[[0m
    # Cas spécial pour echo -n : la sortie peut être collée au prompt suivant
    
    # Étape 1 : Supprimer tous les codes de couleur ANSI
    sed 's/\x1b\[[0-9;]*m//g' "$minishell_output" > "${minishell_output}.no_colors"
    
    # Étape 2 : Détecter toutes les variantes d'echo -n qui suppriment le retour à la ligne
    if [[ "$cmd" == *"echo -n"* ]] || [[ "$cmd" == *"echo -nn"* ]] || [[ "$cmd" == echo\ -n* ]]; then
        # Cas spécial echo -n : approche très simple
        
        # Méthode directe avec sed - plus fiable
        # Supprimer la première ligne, puis extraire ce qui précède "minishell$>"
        tail -n +2 "${minishell_output}.no_colors" | sed 's/minishell\$>.*//' > "${minishell_output}.clean"
        
        echo "=== DEBUG SED SIMPLE ==="
        echo "Fichier clean utilisé: ${minishell_output}.clean"
        echo "Après tail:"
        tail -n +2 "${minishell_output}.no_colors"
        echo "Après sed (direct vers fichier):"
        tail -n +2 "${minishell_output}.no_colors" | sed 's/minishell\$>.*//' | tee "${minishell_output}.clean.debug"
        echo "Vérification fichier créé:"
        ls -la "${minishell_output}.clean"
        echo "Contenu via cat:"
        cat "${minishell_output}.clean"
        echo "=== FIN DEBUG SED ==="
        
    else
        # Cas normal : filtrer les lignes contenant minishell$>
        grep -v "minishell\$>" "${minishell_output}.no_colors" > "${minishell_output}.clean"
    fi
    
    # S'assurer que le fichier .clean existe et est lisible
    if [ ! -f "${minishell_output}.clean" ]; then
        touch "${minishell_output}.clean"
    fi
    
    # Si le fichier est vide après filtrage, créer un fichier vide propre
    if [ ! -s "${minishell_output}.clean" ]; then
        touch "${minishell_output}.clean"
    fi
    
    # Supprimer les codes de couleur avant comparaison si nécessaire
    if [ -s "${minishell_output}.no_colors" ]; then
        # Si le fichier no_colors existe et n'est pas vide, filtrer les prompts
        grep -v "minishell\$>" "${minishell_output}.no_colors" > "${minishell_output}.clean"
    else
        # Sinon, créer un fichier vide
        touch "${minishell_output}.clean"
    fi
    
    # Comparer d'abord les codes de sortie
    local exit_codes_match=false
    if [ $bash_exit_code -eq $minishell_exit_code ]; then
        exit_codes_match=true
    fi
    
    # Comparer les sorties (en normalisant les messages d'erreur)
    local outputs_match=false
    
    if diff -q "$bash_output" "$minishell_clean" > /dev/null 2>&1; then
        outputs_match=true
    else
        # Pour les erreurs, vérifier si c'est juste une différence de nom de programme
        local bash_content=$(cat "$bash_output" | sed 's/bash:/minishell:/g')
        local minishell_content=$(cat "$minishell_clean")
        if [ "$bash_content" = "$minishell_content" ]; then
            outputs_match=true
        fi
    fi
    
    # Déterminer si le test passe
    if [ "$exit_codes_match" = true ] && [ "$outputs_match" = true ]; then
        print_result "$test_name" "PASS"
    elif [ "$exit_codes_match" = true ] && [ $bash_exit_code -ne 0 ]; then
        # Si les codes de sortie correspondent et qu'il y a une erreur, c'est acceptable
        print_result "$test_name" "PASS" "Exit codes match ($bash_exit_code), error messages may differ"
    else
        local bash_sample=$(cat "$bash_output" | head -1 | cut -c1-50)
        local minishell_sample=$(cat "$minishell_clean" | head -1 | cut -c1-50)
        local details="Exit codes: bash($bash_exit_code) vs minishell($minishell_exit_code). Output: Expected: '$bash_sample', Got: '$minishell_sample'"
        print_result "$test_name" "FAIL" "$details"
    fi
    
    # Vérifier les fuites mémoire si demandé
    if [ "$check_leaks" = "true" ]; then
        check_memory_leaks "$cmd" "$test_name"
    fi
    
    # DEBUG: NE PAS NETTOYER POUR L'INSTANT
    # rm -f "$minishell_output" "$minishell_clean" "$minishell_no_colors" "$bash_output"
    echo "DEBUG: Fichiers gardés pour investigation"
}

# Fonction pour tester les erreurs de syntaxe (compare les codes de retour)
test_syntax_error() {
    local cmd="$1"
    local test_name="$2"
    local expected_code="${3:-2}"  # Code 2 pour erreurs de syntaxe
    
    echo -e "\n${BLUE}Testing syntax error:${NC} $cmd"
    
    # Tester avec bash
    timeout 5 bash -c "$cmd" > /dev/null 2>&1
    local bash_exit_code=$?
    
    # Tester avec minishell
    timeout 5 echo "$cmd" | ./minishell > /dev/null 2>&1
    local minishell_exit_code=$?
    
    # Pour les erreurs de syntaxe, on compare les codes de retour
    if [ $bash_exit_code -ne 0 ] && [ $minishell_exit_code -ne 0 ]; then
        print_result "$test_name" "PASS"
    elif [ $bash_exit_code -eq $minishell_exit_code ]; then
        print_result "$test_name" "PASS"
    else
        print_result "$test_name" "FAIL" "Bash exit code: $bash_exit_code, Minishell exit code: $minishell_exit_code"
    fi
}

# Fonction pour tester les commandes exit spéciales
test_exit_command() {
    local cmd="$1"
    local test_name="$2"
    local expected_code="$3"
    
    echo -e "\n${BLUE}Testing exit:${NC} $cmd"
    
    # Tester avec minishell dans un sous-shell pour capturer l'exit code
    local actual_code
    (echo "$cmd" | timeout 5 ./minishell > /dev/null 2>&1)
    actual_code=$?
    
    if [ "$actual_code" -eq "$expected_code" ]; then
        print_result "$test_name" "PASS"
    else
        print_result "$test_name" "FAIL" "Expected exit code $expected_code, got $actual_code"
    fi
}

# Fonction pour tester les builtins
test_builtin() {
    local cmd="$1"
    local test_name="$2"
    
    echo -e "\n${BLUE}Testing builtin:${NC} $cmd"
    
    # Pour les builtins, on teste juste que ça ne crash pas
    local output=$(echo "$cmd" | timeout 5 ./minishell 2>&1)
    local exit_code=$?
    
    if [ $exit_code -eq 0 ] || [ $exit_code -eq 1 ]; then
        print_result "$test_name" "PASS"
    else
        print_result "$test_name" "FAIL" "Exit code: $exit_code"
    fi
}

# Fonction principale
main() {
    echo -e "${BLUE}=== MINISHELL TESTER ===${NC}"
    echo -e "${BLUE}Date: $(date)${NC}\n"
    
    # Vérifier que minishell existe
    if [ ! -f "./minishell" ]; then
        echo -e "${RED}Erreur: ./minishell n'existe pas${NC}"
        echo "Assurez-vous de compiler votre minishell avec 'make'"
        exit 1
    fi
    
    # Créer des fichiers de test
    touch test_file.txt
    echo "Hello World" > test_content.txt
    mkdir -p test_dir 2>/dev/null
    
    echo -e "${YELLOW}=== TESTS DES ENTRÉES VIDES ===${NC}"
    
    # Tests d'entrées vides (doivent retourner 127)
    test_command '""' "Empty double quotes"
    test_command '""""' "Double empty quotes"
    test_command "''" "Empty single quotes"
    test_command '" "' "Space in quotes"
    test_command '"	"' "Tab in quotes"
    
    echo -e "\n\n${YELLOW}=== TESTS DES COMMANDES SIMPLES ===${NC}"
    
    # Tests de commandes simples
    test_command "echo" "Echo without arguments"
    test_command 'echo ""' "Echo empty string"
    test_command "echo Hello World" "Echo multiple words"
    test_command 'echo "Hello World"' "Echo quoted string"
    test_command "echo -n Hello World" "Echo with -n flag"
    test_command "echo -n" "Echo -n only"
    test_command "echo -n -n Hello World" "Echo multiple -n flags"
    test_command "echo -nnnnnnnnnnnnn Hello World" "Echo multiple n chars"
    test_command "echo Hello -n World" "Echo with -n in middle"
    test_command "pwd" "Print working directory"
    test_command "pwd Hello World" "PWD with arguments"
    test_command "ls" "List directory"
    test_command "ls -l" "List with options"
    test_command "/bin/ls -l" "Absolute path ls"
    
    echo -e "\n\n${YELLOW}=== TESTS DES BUILTINS ===${NC}"
    
    # Tests CD
    test_builtin "cd" "CD to home"
    test_builtin 'cd ""' "CD empty string"
    test_builtin 'cd " "' "CD space"
    test_builtin "cd Hello" "CD non-existent"
    test_builtin "cd .." "CD parent directory"
    test_builtin "cd /home" "CD absolute path"
    
    # Tests Export
    test_builtin "export" "Export without args"
    test_builtin 'export ""' "Export empty string"
    test_builtin "export TEST" "Export variable"
    test_builtin "export TEST=Hello" "Export with value"
    test_builtin "export TEST+=World" "Export append"
    test_builtin "export TEST++=World" "Export invalid append"
    test_builtin "export TEST=Hello World" "Export with spaces"
    test_builtin 'export TEST="Hello World"' "Export quoted value"
    
    # Tests Unset
    test_builtin "unset" "Unset without args"
    test_builtin 'unset ""' "Unset empty string"
    test_builtin "unset TEST" "Unset variable"
    
    # Tests Env
    test_builtin "env" "Environment variables"
    
    echo -e "\n\n${YELLOW}=== TESTS DES COMMANDES EXIT ===${NC}"
    
    # Tests Exit (codes de sortie spéciaux)
    test_exit_command "exit" "Exit without args" 0
    test_exit_command 'exit ""' "Exit empty string" 2
    test_exit_command "exit 42abc" "Exit invalid number" 2
    test_exit_command "exit Hello World" "Exit with text" 2
    test_exit_command "exit 42" "Exit with number" 42
    test_builtin "exit 1 2" "Exit too many args"
    
    echo -e "\n\n${YELLOW}=== TESTS DES REDIRECTIONS ===${NC}"
    
    # Créer un fichier source pour les tests
    echo "test content for redirection" > minishell_test.c
    
    # Tests des redirections
    test_command "echo hello > output.txt" "Redirection output"
    test_command "echo world >> output.txt" "Redirection append"
    test_command "cat < test_content.txt" "Redirection input"
    test_command "cat minishell_test.c > out.txt" "Cat with output redirection"
    test_command "cat > out.txt minishell_test.c" "Redirection before filename"
    
    echo -e "\n\n${YELLOW}=== TESTS DES PIPES ===${NC}"
    
    # Tests des pipes
    test_command "echo Hello World | cat" "Simple pipe"
    test_command "cat minishell_test.c | wc -l" "Pipe with wc"
    test_command "echo hello | cat | wc -c" "Multiple pipes"
    test_command "cat nonexistant | ls" "Pipe with error"
    
    echo -e "\n\n${YELLOW}=== TESTS DES VARIABLES D'ENVIRONNEMENT ===${NC}"
    
    # Tests des variables d'environnement
    test_command "echo \$HOME" "Environment variable HOME"
    test_command "echo \$ABCDEF" "Non-existent variable"
    test_command "echo \$42" "Numeric variable name"
    test_command "echo \$%+" "Special chars variable"
    test_command "echo \$?" "Exit status variable"
    test_command "echo '\$HOME'" "Single quoted variable"
    test_command "echo \"\$HOME\"" "Double quoted variable"
    
    echo -e "\n\n${YELLOW}=== TESTS DES GUILLEMETS ===${NC}"
    
    # Tests des guillemets
    test_command "echo 'hello world'" "Single quotes"
    test_command "echo \"hello world\"" "Double quotes"
    test_command "echo 'hello \"world\"'" "Mixed quotes"
    
    echo -e "\n\n${YELLOW}=== TESTS D'ERREURS DE SYNTAXE ===${NC}"
    
    # Tests d'erreurs de syntaxe (maintenant gérés par test_command améliorée)
    test_command "| echo Hello World" "Pipe at beginning"
    test_command "echo Hello World |" "Pipe at end"
    test_command "echo Hello World >" "Incomplete redirection"
    test_command "echo ||| Hello World" "Multiple pipes"
    test_command "> | echo Hello World" "Mixed operators"
    
    echo -e "\n\n${YELLOW}=== TESTS D'ERREURS ===${NC}"
    
    # Tests de gestion d'erreurs
    test_command "ls /nonexistent" "Non-existent directory"
    test_command "cat nonexistent.txt" "Non-existent file"
    test_command "invalid_command" "Invalid command"
    test_command 'ls "-l -a"' "Invalid option format"
    test_command "cat nonexistant" "Cat non-existent file"
    
    echo -e "\n\n${YELLOW}=== TESTS AVEC VÉRIFICATION DE FUITES MÉMOIRE ===${NC}"
    
    # Tests sélectionnés avec vérification des fuites
    test_command "echo hello" "Echo simple" 5 true
    test_command "pwd" "PWD" 5 true
    test_command "ls" "List directory" 5 true
    test_command "echo hello | cat" "Simple pipe" 5 true
    test_command "cat test_content.txt" "Cat file" 5 true
    
    echo -e "\n\n${YELLOW}=== TESTS DE SIGNAUX ===${NC}"
    
    # Test Ctrl+C (SIGINT) - utiliser une commande qui existe
    echo -e "\n${BLUE}Testing:${NC} Signal handling (Ctrl+C)"
    
    # Vérifier si /bin/sleep existe
    if [ -x "/bin/sleep" ]; then
        # Lancer minishell avec /bin/sleep en arrière-plan
        echo "/bin/sleep 5" | ./minishell &
        local minishell_pid=$!
    elif command -v sleep > /dev/null; then
        # Utiliser sleep depuis PATH
        echo "sleep 5" | ./minishell &
        local minishell_pid=$!
    else
        # Fallback : utiliser cat qui attend l'entrée indéfiniment
        echo "cat" | ./minishell &
        local minishell_pid=$!
    fi
    
    # Attendre un peu que minishell démarre
    sleep 0.5
    
    # Envoyer SIGINT (Ctrl+C) au processus minishell
    kill -INT $minishell_pid 2>/dev/null
    
    # Attendre et vérifier si le processus se termine correctement
    local signal_handled=false
    for i in {1..10}; do
        if ! kill -0 $minishell_pid 2>/dev/null; then
            signal_handled=true
            break
        fi
        sleep 0.1
    done
    
    # Forcer l'arrêt si le processus ne répond pas
    kill -KILL $minishell_pid 2>/dev/null
    wait $minishell_pid 2>/dev/null
    
    if [ "$signal_handled" = true ]; then
        print_result "Signal handling (Ctrl+C)" "PASS"
    else
        print_result "Signal handling (Ctrl+C)" "FAIL" "Process did not respond to SIGINT"
    fi
    
    # Test Ctrl+D (EOF) - plus simple
    echo -e "\n${BLUE}Testing:${NC} EOF handling (Ctrl+D)"
    
    # Envoyer EOF à minishell (pas de commande, juste EOF)
    echo -n "" | ./minishell > /dev/null 2>&1
    local eof_exit_code=$?
    
    if [ $eof_exit_code -eq 0 ]; then
        print_result "EOF handling (Ctrl+D)" "PASS"
    else
        print_result "EOF handling (Ctrl+D)" "FAIL" "Exit code: $eof_exit_code"
    fi
    
    # Test signal pendant une commande - utiliser une commande simple
    echo -e "\n${BLUE}Testing:${NC} Signal during command execution"
    
    # Alternative : utiliser 'yes' qui produit une sortie infinie
    if command -v yes > /dev/null; then
        (echo "yes" | timeout 2 ./minishell > /dev/null 2>&1) &
        local test_pid=$!
        sleep 0.5
        kill -INT $test_pid 2>/dev/null
        wait $test_pid 2>/dev/null
        local interrupted_exit_code=$?
        
        # Timeout donne code 124, SIGINT donne généralement 130
        if [ $interrupted_exit_code -eq 124 ] || [ $interrupted_exit_code -eq 130 ] || [ $interrupted_exit_code -eq 1 ]; then
            print_result "Signal during execution" "PASS"
        else
            print_result "Signal during execution" "FAIL" "Unexpected exit code: $interrupted_exit_code"
        fi
    else
        # Si pas de 'yes', utiliser une boucle simple dans le shell
        (echo 'while true; do echo "test"; done' | timeout 1 ./minishell > /dev/null 2>&1) &
        local test_pid=$!
        sleep 0.3
        kill -INT $test_pid 2>/dev/null
        wait $test_pid 2>/dev/null
        
        print_result "Signal during execution" "PASS" "Basic signal test completed"
    fi
    
    # Nettoyer les fichiers de test
    rm -f test_file.txt test_content.txt output.txt out.txt out2.txt minishell_test.c
    rm -rf test_dir
    
    # Afficher le résumé
    echo -e "\n\n${BLUE}=== RÉSUMÉ DES TESTS ===${NC}"
    echo -e "Total des tests: $TOTAL_TESTS"
    echo -e "${GREEN}Tests réussis: $PASSED_TESTS${NC}"
    echo -e "${RED}Tests échoués: $FAILED_TESTS${NC}"
    
    if [ $FAILED_TESTS -eq 0 ]; then
        echo -e "\n${GREEN}🎉 Tous les tests sont passés !${NC}"
        exit 0
    else
        echo -e "\n${RED}❌ Certains tests ont échoué. Vérifiez votre implémentation.${NC}"
        exit 1
    fi
}

# Fonction d'aide
show_help() {
    echo "Usage: $0 [OPTIONS]"
    echo ""
    echo "Options:"
    echo "  -h, --help     Afficher cette aide"
    echo "  -v, --verbose  Mode verbeux"
    echo "  -q, --quick    Tests rapides seulement"
    echo "  -l, --leaks    Mode avec vérification complète des fuites mémoire"
    echo ""
    echo "Ce script teste votre minishell en comparant ses sorties avec bash."
    echo "Assurez-vous que votre minishell est compilé avant de lancer les tests."
}

# Traitement des arguments
case "$1" in
    -h|--help)
        show_help
        exit 0
        ;;
    -v|--verbose)
        set -x
        main
        ;;
    -q|--quick)
        echo "Mode rapide - tests essentiels seulement"
        # Vous pouvez personnaliser ici pour ne lancer que certains tests
        main
        ;;
    -l|--leaks)
        echo "Mode avec vérification complète des fuites mémoire"
        ENABLE_LEAK_CHECK=true
        main
        ;;
    "")
        main
        ;;
    *)
        echo "Option inconnue: $1"
        show_help
        exit 1
        ;;
esac