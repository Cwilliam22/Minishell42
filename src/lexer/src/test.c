/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:45:41 by alexis            #+#    #+#             */
/*   Updated: 2025/04/09 11:58:11 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/lexer.h"

void	test_line(char *input)
{
	t_token		*tokens;
	t_command	*cmds;

	printf("\n\n> TEST: '%s'\n", input);
	
	//Tokenize
	tokens = tokenize(input);
	print_all_tokens(tokens);
	
	//Parse
	cmds = parse(tokens, 0);
	print_all_commands(cmds);

	//Clean
	free_tokens(tokens);
	free_commands(cmds);
}

int	main(void)
{
	//Test basique
	test_line("ls -l");
	test_line("echo hello world");

	//Test avec pipes
	test_line("ls -l | grep .c | wc -l");

	//Test avec redirections
	test_line("ls > output.txt");
	test_line("cat < input.txt > output.txt");
	test_line("command >> append.txt");

	//Test avec guillemets
	test_line("echo \"hello world\"");
	test_line("echo 'hello wrold'");
	test_line("echo \"Guillemets imbriqués'\"");
	test_line("echo 'Guillemets \"imbriqueös\"'");

	//Test avec des cas complexes
	test_line("echo \"mot avec espace\" | grep mot > resultat.txt");
	test_line("echo texte'sans espace'texte");
	test_line("echo \"texte avec $VARIABLE\" et $VARIABLE littérale");

	//Test avec les guillemets non fermés
	test_line("echo \"citation non terminée");
	
	return (0);
}