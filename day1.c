#include "libs/sort.h"
#include "libs/utils.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#define LIST_SIZE 1000
void sum_values(gpointer key, gpointer value, gpointer user_data) {
  int *sum = user_data;
  printf("%d(count) * %d(value) = %d\n", GPOINTER_TO_INT(value),
         GPOINTER_TO_INT(key), GPOINTER_TO_INT(value) * GPOINTER_TO_INT(key));
  *sum += GPOINTER_TO_INT(value) * GPOINTER_TO_INT(key);
}

int main(int argc, char *argv[]) {
  FILE *file1 = fopen("data/day1/list1.txt", "r");
  FILE *file2 = fopen("data/day1/list2.txt", "r");

  // Buffer to store each line of the file.
  char line1[10];
  char line2[10];
  int list1[LIST_SIZE];
  int list2[LIST_SIZE];

  // Check if the file was opened successfully.
  if (file1 != NULL && file2 != NULL) {
    // 'line' buffer.
    int i = 0;
    while (fgets(line1, sizeof(line1), file1) &&
           fgets(line2, sizeof(line2), file2)) {
      // Print each line to the standard output.
      list1[i] = atoi(line1);
      list2[i] = atoi(line2);
      i++;
    }

    // Close the file stream once all lines have been
    // read.
    fclose(file1);
    fclose(file2);
  } else {
    // Print an error message to the standard error
    // stream if the file cannot be opened.
    fprintf(stderr, "Unable to open file!\n");
  }
  mergeSort(list1, LIST_SIZE);
  mergeSort(list2, LIST_SIZE);
  int dist = 0;
  for (int i = 0; i < LIST_SIZE; i++) {
    dist += abs(list1[i] - list2[i]);
  }
  printf("Dist: %d\n", dist);

  // end part 1
  GHashTable *hash_table =
      g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);

  // Initialize hash table with list2 values as keys and 0 as values
  for (int i = 0; i < LIST_SIZE; i++) {
    gpointer key = GINT_TO_POINTER(list2[i]);
    gpointer existing_value = g_hash_table_lookup(hash_table, key);
    int new_count = GPOINTER_TO_INT(existing_value) + 1;
    g_hash_table_insert(hash_table, key, GINT_TO_POINTER(new_count));
  }

  // Sum the counts of list1 numbers found in list2
  int sum = 0;
  for (int i = 0; i < LIST_SIZE; i++) {
    gpointer key = GINT_TO_POINTER(list1[i]);
    gpointer value = g_hash_table_lookup(hash_table, key);
    if (value != NULL) { // If the number from list1 exists in list2
      sum += GPOINTER_TO_INT(value) * list1[i];
    }
  }
  printf("Sum: %d\n", sum);

  // Example of how to look up a value
  // int lookup_value = GPOINTER_TO_INT(g_hash_table_lookup(hash_table,
  // GINT_TO_POINTER(some_key)));

  // When you're done with the hash table
  g_hash_table_destroy(hash_table);
}
