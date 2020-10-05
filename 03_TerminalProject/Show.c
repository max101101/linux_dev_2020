#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

#define DEFAULT_LINES_SIZE 256
#define HEADER_SIZE 3
#define ESC_BUTTON 27

struct internal_file {
	char* name;
	char** lines;
	size_t length;
};

struct internal_file* read_file(FILE* f) {
	struct internal_file* res = realloc(NULL, sizeof(struct internal_file));
	if (res == NULL) {
		return NULL;
	}
	res->length = 0;

	size_t lines_size = DEFAULT_LINES_SIZE;
	res->lines = realloc(NULL, sizeof(char*) * lines_size);
	if (res->lines == NULL) {
		return NULL;
	}

	size_t len_line = 0;
	ssize_t read;
	while ((read = getline(&(res->lines[res->length++]), &len_line, f)) != -1) {
		if (res->length == lines_size) {
			lines_size = lines_size * 2;
			res->lines = realloc(res->lines, sizeof(char*) * lines_size);
			if (res->lines == NULL) {
				return NULL;
			}
		}
	}

	return res;
}

void show_file(struct internal_file* file) {
	int position = 0;

	initscr();
	noecho();
	cbreak();
	WINDOW* w = newwin(LINES, COLS, 0, 0);
	refresh();

	char end = 0;
	while (!end) {
		werase(w);
		wmove(w, 0, 0);
		wprintw(w, "%s\n\n", file->name);
		for (int i = position, line = 0; (line < LINES - HEADER_SIZE) && (i < file->length); line += 1, i++) {
			wprintw(w, "%6d: %s", i + 1, file->lines[i]);
		}
		wrefresh(w);

		int c = getch();
		switch (c) {
			case ' ':
				if (LINES + position - HEADER_SIZE < file->length) {
					position++;
				}
				break;
			case ESC_BUTTON:
				end = 1;
		}
	}
	endwin();
}

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "No input file, usage: show <file_name>\n");
		return 1;
	}
	char* file_name = argv[1];

	FILE* f = fopen(file_name, "r");
	if (f == NULL) {
		fprintf(stderr, "Can't open file '%s'\n", file_name);
		return 1;
	}

	struct internal_file* file = read_file(f);
	if (file == NULL) {
		fprintf(stderr, "Can't read file '%s'\n", file_name);
		return 1;
	}
	file->name = file_name;
	fclose(f);

	show_file(file);

	for (int i = 0; i < file->length; i++) {
		free(file->lines[i]);
	}
	free(file->lines);
	free(file);

	return 0;
}
