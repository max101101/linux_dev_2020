/** @file guess.c
 * Main file.
 *
 * Implements game that tries to guess player's number from
 * 1 to 100 using interval halving method.
 *
 * Can work with roman and decimal numbers.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

/**
 * Table for converting decimal-roman.
 */
const char *romans[] = {"" /* 0 */, "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII",
			"XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI",
			"XXVII", "XXVIII", "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII",
			"XXXVIII", "XXXIX", "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII",
			"XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX", "LXI",
			"LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII",
			"LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII",
			"LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC", "XCI", "XCII",
			"XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"};

/**
 * Return roman string representation of decimal number.
 */
const char* to_roman(int n) {
	return romans[n];
}

/**
 * Return string representation of decimal number in decimal or roman format.
 */
const char* str_rep(int n, char roman) {
	if (roman) {
		return to_roman(n);
	}
	static char str[4];
	sprintf(str, "%d", n);
	return str;
}

/**
 * Prints help message.
 */
void help(char e, int code) {
	char *m = _(
		"Usage:\n"
		"	guess [options]\n"
		"Options:\n"
		"	-r              Use Roman numerals\n"
		"	-h | --help	Show this message\n"
		"\n");

	fprintf(stderr, "%s", m);
	if (e) {
		exit(code);
	}	   
}


int main(int argc, char** argv) {
	setlocale(LC_ALL, "");
	bindtextdomain("guess", ".");
	textdomain("guess");

	char roman = 0;
	for (int i = 1; i < argc; i++) {
		if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0)) {
			help(1, 0);
		} else if (strcmp(argv[i], "-r") == 0) {
			roman = 1;
		} else {
			help(1, 1);
		}
	}

	int start = 1;
	int end = 100;
	printf("%s %s", _("Guess a number in range"), str_rep(1, roman));
	printf("-%s\n", str_rep(100, roman));

	while(1) {
		if(end - start < 2) {
			printf("%s: %s\n", _("You Guessed"), str_rep(end, roman));
			break;
		}	

		printf("%s: %s? (%s|%s)\n", _("Is your number bigger than"), str_rep(start + (end-start)/2, roman), _("yes"), _("no"));

		char ans[32];
		scanf("%s", ans);
		if (!strcmp(ans, _("yes"))) {
			start = start + (end-start)/2;
			continue;
		}

		if (!strcmp(ans, _("no"))) {
			end = start + (end-start)/2;
			continue;
		}	
	}

	return 0;
}
