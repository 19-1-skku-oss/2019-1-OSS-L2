#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <map>
#include <string>

#define TOTAL_TEST_CASE 100

#define MAX_TABLE 300 
#define MAX_KEY 8 
#define MAX_DATA 2000
#define DELETE_COUNT 1000

using namespace std;

struct Node {
		char key[MAX_KEY];
			int value;
				Node * next;
};

Node * tb[MAX_TABLE]; 
char keys[MAX_DATA][MAX_KEY]; 
int values[MAX_DATA];

void init() {

		
		for (int i = 0; i < MAX_TABLE; ++i) {
					Node * cur = tb[i];
							Node * tmp;
									while (cur != NULL) {
													tmp = cur;
																cur = cur->next;
																			free(tmp);
																					}
											tb[i] = NULL;
												}

			
			srand(time(NULL));


				for (int i = 0; i < MAX_DATA; ++i) {
							values[i] = rand() % 100 + 1;
								}

					
					for (int i = 0; i < MAX_DATA; ++i) {
								for (int j = 0; j < MAX_KEY - 1; ++j) {
												keys[i][j] = rand() % 26 + 97; // ASCII 97 ~ 122
														}
										keys[i][MAX_KEY - 1] = '\0';
											}

}

void my_str_cpy(char * dest, const char * src) {

		while (*src != '\0') {
					*dest = *src;
							dest++; src++;
								}
			*dest = '\0';

}

int my_str_cmp(const char * str1, const char * str2) {

		while (*str1 != '\0' && (*str1 == *str2)) {
					str1++;
							str2++;
								}
			return *str1 - *str2;

}

int my_hash(const char * str) {
		int hash = 401;

			while (*str != '\0') {
						hash = ((hash << 4) + (int)(*str)) % MAX_TABLE;
								str++;
									}

				return hash % MAX_TABLE;
}

void add(const char * key, int value) {

		Node * new_node = (Node *)malloc(sizeof(Node));
			my_str_cpy(new_node->key, key);
				new_node->value = value;
					new_node->next = NULL;

						int index = my_hash(key);


							if (tb[index] == NULL) {
										tb[index] = new_node;
											}

								else {

											Node * cur = tb[index];

													while (cur != NULL) {

																	
																	if (my_str_cmp(cur->key, key) == 0) {
																						cur->value = value;
																										return;
																													}

																				cur = cur->next;
																						}
															
															new_node->next = tb[index];
																	tb[index] = new_node;
																		}
}

bool find(const char * key, int * val) {

		int index = my_hash(key);

			Node * cur = tb[index];


				while (cur != NULL) {
							if (my_str_cmp(cur->key, key) == 0) {
											*val = cur->value;
														return true;
																}
									cur = cur->next;
										}

					return false;

}

bool destroy(const char * key) {

		int index = my_hash(key);

			
			if (tb[index] == NULL) {
						return false;
							}


				if (my_str_cmp(tb[index]->key, key) == 0) {
							Node * first = tb[index];
									tb[index] = tb[index]->next;
											free(first);
													return true;
														}

					
					else {

								Node * cur = tb[index]->next;
										Node * prev = tb[index];

												while (cur != NULL && my_str_cmp(cur->key, key) != 0) {
																prev = cur;
																			cur = cur->next;
																					}

														if (cur == NULL) return false;

																prev->next = cur->next;
																		free(cur);
																				return true;
																					}
}

void print_hash() {

		for (int i = 0; i < MAX_TABLE; ++i) {
					if (tb[i] != NULL) {

									printf("index : %d\n", i);

												Node * cur = tb[i];

															while (cur != NULL) {
																				printf("{ %s, %d }, ", cur->key, cur->value);
																								cur = cur->next;
																											}
																		printf("\n");
																				}
						}

}

int main() {

		int test_case = 1;
			int correct = 0;


				for (test_case = 1; test_case <= TOTAL_TEST_CASE; ++test_case) {

							init();

									bool is_equal = true;

											map<string, int> m;
													map<string, int>::iterator it;


															for (int i = 0; i < MAX_DATA; ++i) {
																			add(keys[i], values[i]);
																					}
																	for (int i = 0; i < MAX_DATA; ++i) {
																					if (m.count(keys[i]) == 0) {
																										m.insert(make_pair(keys[i], values[i]));
																													}
																								else {
																													m[keys[i]] = values[i];
																																}

																										}

																			for (int i = 0; i < MAX_DATA; ++i) {

																							int tmp;
																										find(keys[i], &tmp);

																													if (m[keys[i]] != tmp) {
																																		is_equal = false;
																																					}
																															}

																					char tmp_key[MAX_KEY];
																							for (int i = 0; i < DELETE_COUNT; ++i) {
																											my_str_cpy(tmp_key, keys[rand() % MAX_DATA]);
																														destroy(tmp_key);
																																	m.erase(tmp_key);
																																			}

																									for (int i = 0; i < MAX_DATA; ++i) {

																													int tmp = -1;

																																if (find(keys[i], &tmp) == false && m.count(keys[i]) == 0) {
																																					continue;
																																								}

																																			if (find(keys[i], &tmp) == true && m.count(keys[i]) == 1 && m[keys[i]] == tmp) {
																																								continue;
																																											}
																																						else {
																																											is_equal = false;
																																														}

																																								}

																											if (is_equal) correct++;

																												}

					printf("Total : %d / %d\n", correct, TOTAL_TEST_CASE);

						return 0;
}
