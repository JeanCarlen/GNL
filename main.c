#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#if BONUS == 1
# include "get_next_line_bonus.h"
#else
# include "get_next_line.h"
#endif

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"


int	check_line(char *line, char *expected, const char *test_name)
{
	int	pass = 0;

	if (line == NULL && expected == NULL)
	{
		pass = 1;
	}
	else if (line != NULL && expected != NULL && strcmp(line, expected) == 0)
	{
		pass = 1;
	}

	if (pass)
	{
		printf(GREEN "[OK]" RESET " Test: %s\n", test_name);
	}
	else
	{
		printf(RED "[KO]" RESET " Test: %s\n", test_name);
		printf(RED "      Attendu: >%s<\n" RESET, expected);
		printf(RED "      Obtenu:  >%s<\n" RESET, line);
	}

	if (line)
		free(line);
	
	return (pass);
}

int	test_single_fd(void)
{
	int		fd;
	int		tests_ok = 0;
	int		total_tests = 0;
	char	*line;

	printf("\n--- Test de base (Single FD) ---\n");

	fd = open("tests/test1.txt", O_RDONLY);
	if (fd == -1) { printf("Erreur: 'tests/test1.txt' introuvable.\n"); return (0); }
	tests_ok += check_line(get_next_line(fd), "ligne 1\n", "test1.txt: Ligne 1"); total_tests++;
	tests_ok += check_line(get_next_line(fd), "ligne 2\n", "test1.txt: Ligne 2"); total_tests++;
	tests_ok += check_line(get_next_line(fd), "ligne 3\n", "test1.txt: Ligne 3"); total_tests++;
	tests_ok += check_line(get_next_line(fd), "ligne 4",   "test1.txt: Ligne 4 (sans \\n)"); total_tests++;
	tests_ok += check_line(get_next_line(fd), NULL,        "test1.txt: Fin (NULL)"); total_tests++;
	close(fd);

	fd = open("tests/empty.txt", O_RDONLY);
	if (fd == -1) { printf("Erreur: 'tests/empty.txt' introuvable.\n"); return (0); }
	tests_ok += check_line(get_next_line(fd), NULL, "empty.txt: Fin (NULL)"); total_tests++;
	close(fd);

	tests_ok += check_line(get_next_line(-1), NULL, "FD invalide (-1)"); total_tests++;
	tests_ok += check_line(get_next_line(99), NULL, "FD non ouvert (99)"); total_tests++;

	printf("\n--- Test STDIN (FD 0) ---\n");
	printf("Veuillez taper 'bonjour' et appuyer sur Entrée :\n");
	line = get_next_line(0);
	tests_ok += check_line(line, "bonjour\n", "STDIN: 'bonjour'"); total_tests++;
	
	fd = open("tests/newline.txt", O_RDONLY);
	if (fd == -1) { printf("Erreur: 'tests/newline.txt' introuvable.\n"); return (0); }
	tests_ok += check_line(get_next_line(fd), "\n",   "newline.txt: Ligne 1 (\\n)"); total_tests++;
	tests_ok += check_line(get_next_line(fd), NULL,   "newline.txt: Fin (NULL)"); total_tests++;
	close(fd);

	fd = open("tests/multi_nl.txt", O_RDONLY);
	if (fd == -1) { printf("Erreur: 'tests/multi_nl.txt' introuvable.\n"); return (0); }
	tests_ok += check_line(get_next_line(fd), "ligne 1\n", "multi_nl.txt: Ligne 1"); total_tests++;
	tests_ok += check_line(get_next_line(fd), "\n",        "multi_nl.txt: Ligne 2 (vide)"); total_tests++;
	tests_ok += check_line(get_next_line(fd), "\n",        "multi_nl.txt: Ligne 3 (vide)"); total_tests++;
	tests_ok += check_line(get_next_line(fd), "fin",       "multi_nl.txt: Ligne 4 (sans \\n)"); total_tests++;
	tests_ok += check_line(get_next_line(fd), NULL,        "multi_nl.txt: Fin (NULL)"); total_tests++;
	close(fd);

	printf("\n--- Résultat Single FD: %d / %d tests passés ---\n", tests_ok, total_tests);
	return (tests_ok == total_tests);
}

int	test_multi_fd(void)
{
	int		fd1, fd2;
	int		tests_ok = 0;
	int		total_tests = 0;

	printf("\n--- Test BONUS (Multi-FD) ---\n");
	
	fd1 = open("tests/test1.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1) { printf("Erreur: Fichiers de test introuvables.\n"); return (0); }

	tests_ok += check_line(get_next_line(fd1), "ligne 1\n", "Multi-FD: FD1 Ligne 1"); total_tests++;
	tests_ok += check_line(get_next_line(fd2), "Bonjour\n", "Multi-FD: FD2 Ligne 1"); total_tests++;
	tests_ok += check_line(get_next_line(fd1), "ligne 2\n", "Multi-FD: FD1 Ligne 2"); total_tests++;
	tests_ok += check_line(get_next_line(fd2), "le\n",      "Multi-FD: FD2 Ligne 2"); total_tests++;
	tests_ok += check_line(get_next_line(fd1), "ligne 3\n", "Multi-FD: FD1 Ligne 3"); total_tests++;
	tests_ok += check_line(get_next_line(fd2), "monde\n",   "Multi-FD: FD2 Ligne 3"); total_tests++;
	tests_ok += check_line(get_next_line(fd1), "ligne 4",   "Multi-FD: FD1 Ligne 4 (sans \\n)"); total_tests++;
	tests_ok += check_line(get_next_line(fd2), "\n",        "Multi-FD: FD2 Ligne 4 (vide)"); total_tests++;
	tests_ok += check_line(get_next_line(fd1), NULL,        "Multi-FD: FD1 Fin (NULL)"); total_tests++;
	tests_ok += check_line(get_next_line(fd2), "fin",       "Multi-FD: FD2 Ligne 5 (sans \\n)"); total_tests++;
	tests_ok += check_line(get_next_line(fd2), NULL,        "Multi-FD: FD2 Fin (NULL)"); total_tests++;

	close(fd1);
	close(fd2);

	printf("\n--- Résultat Multi-FD: %d / %d tests passés ---\n", tests_ok, total_tests);
	return (tests_ok == total_tests);
}

int	main(void)
{
#if BONUS == 1
	printf("--- Compilation en mode BONUS --- \n");
	
	int	res1 = test_single_fd();
	int	res2 = test_multi_fd();

	if (res1 && res2)
		printf(GREEN "\n>>> TOUS LES TESTS BONUS SONT PASSÉS <<<\n" RESET);
	else
		printf(RED "\n>>> ÉCHEC DES TESTS BONUS <<<\n" RESET);

#else
	printf("--- Compilation en mode MANDATORY --- \n");
	
	int res1 = test_single_fd();

	if (res1)
		printf(GREEN "\n>>> TOUS LES TESTS MANDATORY SONT PASSÉS <<<\n" RESET);
	else
		printf(RED "\n>>> ÉCHEC DES TESTS MANDATORY <<<\n" RESET);

#endif

	return (0);
}
