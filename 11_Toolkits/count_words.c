#include <stdio.h>
#include <glib.h>
#include <glib/gprintf.h>

gint compare_func(gconstpointer a, gconstpointer b, gpointer userdata) {
	return (gint)g_hash_table_lookup(userdata, b) - (gint)g_hash_table_lookup(userdata, a);
}

void print(gpointer data, gpointer userdata) {
	g_printf("%s %d\n", data, (gint)g_hash_table_lookup(userdata, data));
}

void key_destroy_func(gpointer data) {
	g_free(data);
}

int main() {
	int N = 80;
	char input[N];
	GHashTable* words = g_hash_table_new_full(g_int_hash,  g_str_equal, key_destroy_func, NULL);

	while (fgets(input, N, stdin) != NULL) {
		gchar** split = g_strsplit_set(input, " .,\t\n", -1);
		gchar** p = split;

		while (*p) {
			if (!g_strcmp0(*p, "")) {
				p++;
				continue;
			}

			g_hash_table_insert(words, *p, (gpointer)((glong)g_hash_table_lookup(words, *p) + 1));

			p++;
		}

		g_free(split);
	}

	GList* keys = g_hash_table_get_keys(words);
	keys = g_list_sort_with_data(keys, compare_func, words);
	g_list_foreach(keys, print, words);
	
	g_list_free(keys);
	g_hash_table_destroy(words);

	return 0;
}
