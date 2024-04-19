#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct Node {
    struct Node *children[ALPHABET_SIZE];
    int isEndOfWord;
};

// trie structure
struct Trie
{	
    struct Node *root;
};

struct Node *createNode() {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode) {
        newNode->isEndOfWord = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

void insert(struct Trie *pTrie, char *word)
{
    struct Node *current = pTrie->root;
    int index;
    for (int i = 0; i < strlen(word); i++) {
        index = word[i] - 'a';
        if (!current->children[index]) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    current->isEndOfWord++;
}

// computes the number of occurrences of the word
int numberOfOccurrences(struct Trie *pTrie, char *word)
{
    struct Node *current = pTrie->root;
    int index;

    for (int i = 0; i < strlen(word); i++) {
        index = word[i] - 'a';
        if (!current->children[index]) {
            return 0;
        }
        current = current->children[index];

    }
    return current->isEndOfWord;
}

void deallocateNodes(struct Node *root) {
    if (root) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            deallocateNodes(root->children[i]);
        }
        free(root);
    }
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie) {
        deallocateNodes(pTrie->root);
        free(pTrie);
    }
    return NULL;
}

// initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *trie = (struct Trie *)malloc(sizeof(struct Trie));
    if (trie) {
        trie->root = createNode();
    }
    return trie;
}

// this function will return number of words in the dictionary,
// and put all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    char *inputFileName = "dictionary.txt";
    int n;

    FILE *file = freopen(inputFileName, "r", stdin);
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    if (scanf("%d", &n) != 1)
    {
        printf("Error reading from file.\n");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        char word[100];
        if (scanf("%s", word) != 1) {
            printf("Error reading word from file.\n");
            fclose(file);
            return -1;
        }
        pInWords[i] = strdup(word);
    }
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}