#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#include "config.h"

#define _(STRING) gettext(STRING)

int main() {
	setlocale(LC_ALL, "");
	bindtextdomain("guess", LOCALEDIR);
	textdomain("guess");

	int start = 1;
	int end = 100;
	printf("%s\n", _("Guess a number in range 1-100"));

	while(1) {
		if(end - start < 2) {
			printf("%s: %d\n", _("You Guessed"), end);
			break;
		}	

		printf("%s: %d? (%s|%s)\n", _("Is your number bigger than"), start + (end-start)/2, _("yes"), _("no"));

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
