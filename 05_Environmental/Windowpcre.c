#ifndef PCRE2_CODE_UNIT_WIDTH
#define PCRE2_CODE_UNIT_WIDTH 8
#endif

#ifdef WITHOUT_UTF
#define PCRE2_UCP_CONFIGURED 0
#else
#define PCRE2_UCP_CONFIGURED PCRE2_UCP
#endif

#include <stdio.h>
#include <string.h>
#include <pcre2.h>
#include <ncurses.h>

#define DX 3
#define ONLELINE 3
#define MAXSTR 80

void pcre(WINDOW* winO, PCRE2_SPTR pattern, PCRE2_SPTR subject)
{
	pcre2_code *re;

	int errnum;
	int i, rc;

	PCRE2_SIZE erroffs;
	PCRE2_SIZE *ovector;
	PCRE2_SIZE subject_length;

	pcre2_match_data *match_data;

	subject_length = (PCRE2_SIZE)strlen((char *)subject);

	re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_UCP_CONFIGURED, &errnum, &erroffs, NULL);

	if (re == NULL) {
		PCRE2_UCHAR buffer[256];
		pcre2_get_error_message(errnum, buffer, sizeof(buffer));
		wprintw(winO, "PCRE2 compilation failed at offset %d: %s\n", (int)erroffs,
			buffer);
		return; 
	}

	match_data = pcre2_match_data_create_from_pattern(re, NULL);

	rc = pcre2_match(re, subject, subject_length, 0, 0, match_data, NULL);

	if (rc < 0) {
		switch(rc) {
		case PCRE2_ERROR_NOMATCH:
			wprintw(winO, "No match\n");
			break;
		default:
			wprintw(winO, "Matching error %d\n", rc);
			break;
		}
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return;
	}

	ovector = pcre2_get_ovector_pointer(match_data);

	for (i = 0; i < rc; i++)
		wprintw(winO, " %2ld: %.*s\n", ovector[2*i], 
			(int)(ovector[2*i+1] - ovector[2*i]),
			subject + ovector[2*i]);

	pcre2_match_data_free(match_data);
	pcre2_code_free(re);

	return; 
}

int main() {
	WINDOW *winA, *winB, *winO;
	char inA[MAXSTR], inB[MAXSTR];
	int half;

	initscr();
	cbreak();
	printw("Input:");
	refresh();

	half = (COLS-2*DX)/2;
	winA = newwin(ONLELINE, half, DX, DX);
	winB = newwin(ONLELINE, half, DX, DX+half);
	winO = newwin(LINES-ONLELINE-DX*2, (COLS-2*DX), DX+ONLELINE, DX);
	keypad(winA, TRUE);
	keypad(winB, TRUE);
	scrollok (winO, TRUE);

	wmove(winO, 1, 0);
	do {
		werase(winA); box(winA, 0, 0);
		mvwgetnstr(winA, 1, 1, inA, MAXSTR);
		werase(winB); box(winB, 0, 0);
		mvwgetnstr(winB, 1, 1, inB, MAXSTR);
		pcre(winO, (PCRE2_SPTR)inA, (PCRE2_SPTR)inB);
		box(winO, 0, 0);
		wrefresh(winO);
	} while(*inA);

	endwin();

	return 0;
}
