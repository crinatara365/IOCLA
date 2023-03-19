#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LINE_SIZE 300

struct Dir;
struct File;

typedef struct Dir{
	char *name;
	struct Dir* parent; 
	struct File* head_children_files; 
	struct Dir* head_children_dirs; 
	struct Dir* next; 
} Dir;

typedef struct File {
	char *name;
	struct Dir* parent; 
	struct File* next; 
} File;

void touch (Dir* parent, char* name) {
	int contor = 0;
	File *file = malloc(sizeof(File));
	if(!file) printf("Nu s-a reusit alocarea\n");
	if(parent->head_children_files == NULL) { 
		/* nu e niciun fisier in lista, deci inserez direct */
		file->name = malloc(30);
		if(!file->name) printf("Nu s-a reusit alocarea\n");
		strcpy(file->name, name);
		file->parent = parent;
		file->next = NULL;
		parent->head_children_files = file; 
	} 
	else { 
		/* mai sunt fisiere in lista */
		File *aux = malloc(sizeof(File));
		if(!aux) printf("Nu s-a reusit alocarea\n");
		aux = parent->head_children_files;
		if(strcmp(aux->name,name) == 0) { //daca primul fisier are acelasi nume
				printf("File already exists\n");
				contor++;
			}
		if(contor == 0)
			while(aux->next != NULL) { 
				aux = aux->next;
				if(strcmp(aux->name,name) == 0) { 
					printf("File already exists\n");
					contor++;
				}
			}
		if(contor == 0) {
			file->name = malloc(30);
			if(!file->name) printf("Nu s-a reusit alocarea\n");
			strcpy(file->name, name);
			file->parent = parent;
			file->next = NULL;
			aux->next = file;
		} 
	}
} 

void mkdir (Dir* parent, char* name) {
	int contor = 0;
	Dir *director = malloc(sizeof(Dir));
	if(!director) printf("Nu s-a reusit alocarea\n");
	if(parent->head_children_dirs == NULL) { 
		/* nu e niciun director in lista, deci adaugam */
		director->name = malloc(30);
		if(!director->name) printf("Nu s-a reusit alocarea\n");
		strcpy(director->name, name);
		director->parent = parent;
		director->next = NULL;
		director->head_children_dirs = NULL;
		director->head_children_files = NULL;
		/* setam pointerul catre primul director din sistemul de fisiere */
		parent->head_children_dirs = director; 
	}
	else { 
		/* exista un director in lista, deci verificam daca exista deja */
		Dir *aux = malloc(sizeof(Dir));
		if(!aux) printf("Nu s-a reusit alocarea\n");
		aux = parent->head_children_dirs;
		if(strcmp(aux->name,name) == 0) { 
				/* daca primul director are acelasi nume */
				printf("Directory already exists\n");
				contor++;
			}
		if(contor == 0)
			while(aux->next != NULL) { 
				/* daca celelalte directoare au acelasi nume */
				aux = aux->next;
				if(strcmp(aux->name,name) == 0) { 
					printf("Directory already exists\n");
					contor++;
				}
			}
		if(contor == 0) { 
			/* nu exista deja, deci adaugam la final */ 
			director->name = malloc(30);
			if(!director->name) printf("Nu s-a reusit alocarea\n");
			strcpy(director->name, name);
			director->parent = parent;
			director->next = NULL;
			director->head_children_dirs = NULL;
			director->head_children_files = NULL;
			aux->next = director;
		} 
	}
	
}

void ls (Dir* parent) {
	File *aux = malloc(sizeof(File)); 
	Dir *aux2 = malloc(sizeof(Dir));
	if(!aux) printf("Nu s-a reusit alocarea\n");
	if(!aux2) printf("Nu s-a reusit alocarea\n");
	aux = parent->head_children_files; 
	aux2 = parent->head_children_dirs;
	if(aux == NULL && aux2 == NULL) {
		return;
	}
	else {
		while(aux2 != NULL)
		{
			printf("%s\n", aux2->name);
			aux2 = aux2->next;
		}
		while(aux != NULL)
		{
			printf("%s\n", aux->name);
			aux = aux->next;
		}
	}
}

void rm (Dir* parent, char* name) {
	int contor = 0;
	File *aux = malloc(sizeof(File));
	if(!aux) printf("Nu s-a reusit alocarea\n");
	aux = parent->head_children_files;
	if(aux == NULL) { 
		/* nu exista fisiere in director */
		printf("Could not find the file\n");
		return;
	}
	if(strcmp(aux->name, name) == 0) { 
		/* daca primul fisier e cel cautat */
		parent->head_children_files = aux->next;
		free(aux->name);
		free(aux);
		contor++;
	}
	else { 
		/* daca e printre urmatoarele */
		File *aux2 = malloc(sizeof(File));
		if(!aux2) printf("Nu s-a reusit alocarea\n");
		for(aux2 = aux->next; aux2 != NULL; aux = aux2, aux2 = aux2->next) {
			if(strcmp(aux2->name, name) == 0) { 
				/* daca gasim fisierul dat, stergem */
				aux->next = aux2->next;
				free(aux2->name);
				free(aux2);
				contor++;
			}
		}
	} 
	if(contor == 0) printf("Could not find the file\n");
}

void rmdir (Dir* parent, char* name) {
	int contor = 0;
	Dir *director = malloc(sizeof(Dir));
	if(!director) printf("Nu s-a reusit alocarea\n");
	director = parent->head_children_dirs;
	if(director == NULL) {  
		/* nu exista directoare cu numele dat, deci cautam fisiere */
		printf("Could not find the dir\n");
		return;
	}
	if(strcmp(director->name, name) == 0) { 
		/* daca primul director e cel cautat */
		parent->head_children_dirs = director->next;
		free(director->name);
		free(director);
		contor++;
	}
	else { 
		Dir *director2 = malloc(sizeof(Dir));
		if(!director2) printf("Nu s-a reusit alocarea\n");
		for(director2 = director->next; director2 != NULL; director = director2, director2 = director2->next) {
			if(strcmp(director2->name, name) == 0) { 
				director->next = director2->next;
				free(director2->name);
				free(director2);
				contor++;
			}
		}
	} 
	if(contor == 0) printf("Could not find the dir\n");
}

void cd(Dir** parent, char *name) {
	if(strcmp(name, "..") == 0) {
		/* daca directorul curent nu are director parinte */
		if((*parent)->parent == NULL) 
			return;
		else
			*parent = (*parent)->parent;
	}
	else {
		Dir *director = malloc(sizeof(Dir));
		if(!director) printf("Nu s-a reusit alocarea\n");
		/* verificam daca name se afla printre directoarele din directorul curent */
		for(director = (*parent)->head_children_dirs; director != NULL; director = director->next) {
			if(strcmp(director->name, name) == 0) { 
				*parent = director; //ne mutam 
				return;
			}
		}
		printf("No directories found!\n");
	}
}

char *pwd (Dir* target) {
	char *string = malloc(100);
	char *aux = malloc(100);
	if(target->parent == NULL) { 
		/* cand se ajunge la "home" */
		strcpy(string, "/home");
		return string;
	}
	while(target->parent != NULL) {
		aux = pwd(target->parent);
		break;
	}
	if(aux != NULL) {
		strcat(aux, "/");
		strcat(aux, target->name);
	}
	return aux;
}

void stop (Dir* target) {
	exit(0);
}

void tree (Dir* target, int level) {
	Dir *director = malloc(sizeof(Dir));
	if(!director) printf("Nu s-a reusit alocarea\n");
	director = target->head_children_dirs;
	if(level != 0 && director != NULL) {
		for(int i = 1; i <= level; i++)
			printf("    ");
		printf("%s\n",director->name);
	}
	/* daca nu exista niciun director in parinte */
	if(director == NULL && level == 0) { 
		File *aux = target->head_children_files;
		while(aux != NULL) { //verific daca exista vreun fisier
			printf("%s\n", aux->name);
			aux = aux->next;
		}
	} 
	/* atata timp cat se gasesc directoare in parinte */
	while(director != NULL) { 
		if(level == 0) 
			printf("%s\n",director->name);
		if(director->head_children_dirs != NULL) 
			tree(director,level+1);

		/* se cauta fisiere */
		File *aux = target->head_children_files; 
		while(aux != NULL) { //afisez fisierele
			if(level == 0) printf("%s\n",aux->name);
			else {
				for(int i = 1; i < level; i++)
					printf("    ");
				printf("    %s\n", aux->name); 
			}
			aux = aux->next;
		} 
		level = 0;
		director = director->next;
	}
	/* se verifica daca dupa toate directoarele, mai exista si fisiere */
	if(level == 0 && director != NULL) { 
		File *aux2 = target->head_children_files; 
		while(aux2 != NULL) {
			printf("%s\n", aux2->name);
			aux2 = aux2->next;
		}
	}
}

void mv(Dir* parent, char *oldname, char *newname) {
	int contor1 = 0, contor2 = 0, contor3 = 0, contor4 = 0;
	File *file = parent->head_children_files;
	Dir *director = parent->head_children_dirs;
	/* se verifica daca oldname si newname exista */
	for(; file != NULL; file = file->next) { 
		if(strcmp(oldname, file->name) == 0) 
			contor1++;
		if(strcmp(newname, file->name) == 0) 
			contor3++;
	} 
	while(director != NULL) { 
		if(strcmp(oldname, director->name) == 0) 
			contor2++;
		if(strcmp(newname, director->name) == 0)
			contor4++;
		director = director->next;
	}
	if(contor1 == 0 && contor2 == 0) { 
		printf("File/Director not found\n");
		return;
	}
	if(contor3 != 0 || contor4 != 0) { 
		printf("File/Director already exists\n");
		return;
	}
	/* s-a gasit fisier, deci se modifica */
	if(contor1 == 1) { 
		File *aux = parent->head_children_files;
		/* daca trebuie modificat primul fisier */
		if(strcmp(aux->name, oldname) == 0) {  
			/* il stergem de la inceput */
			parent->head_children_files = parent->head_children_files->next; 
			/* il adaugam la final */
			touch(parent, newname); 
			return; 
		}
		for(; aux->next != NULL; aux = aux->next)
			if(strcmp(aux->next->name, oldname) == 0) { 
				/* il stergem din lista */
				aux->next = aux->next->next; 
			}
		touch(parent, newname); 
		return;
	}
	/* s-a gasit director, deci il modificam */
	if(contor2 == 1) { 
		Dir *aux = parent->head_children_dirs;
		if(strcmp(aux->name, oldname) == 0) { 
			if(aux->head_children_dirs == NULL && aux->head_children_files == NULL) { 
				mkdir(parent, newname); 
				parent->head_children_dirs = parent->head_children_dirs->next; 
				return;
			}
			/* directorul nu este gol */
			else { 
				Dir *aux2 = parent->head_children_dirs;
				for(; aux->next != NULL; aux = aux->next); 
				mkdir(parent, newname); 
				parent->head_children_dirs = parent->head_children_dirs->next; 
				return;
			}
		}
	}
}

int main () {
	Dir *parent = malloc(sizeof(Dir));
	if(!parent) printf("Nu s-a reusit alocarea\n");
	parent->name = malloc(30);
	if(!parent->name) printf("Nu s-a reusit alocarea\n");
	strcpy(parent->name, "home");
	parent->parent = NULL;
	char *input = malloc(100 * sizeof(char));
	if(!input) printf("Error\n");
	while(fgets(input, 100, stdin))
	{
		char *comanda = strtok(input, " ");
		/* se elimina spatiul de la finalul cuvantului */
		if(comanda[strlen(comanda) - 1] == '\n')
			comanda[strlen(comanda) - 1] = '\0';
		if(comanda[strlen(comanda) - 1] == '\r')
			comanda[strlen(comanda) - 1] = '\0';
		
		if(strcmp(comanda, "touch") == 0) {
			char *nume = strtok(NULL, " ");
			
			if(nume[strlen(nume) - 1] == '\n')
				nume[strlen(nume) - 1] = '\0';
			if(nume[strlen(nume) - 1] == '\r')
				nume[strlen(nume) - 1] = '\0'; 
			touch(parent, nume);
		} 

		if(strcmp(comanda, "mkdir") == 0) {
			char *nume = strtok(NULL, " ");
			
			if(nume[strlen(nume) - 1] == '\n')
				nume[strlen(nume) - 1] = '\0';
			if(nume[strlen(nume) - 1] == '\r')
				nume[strlen(nume) - 1] = '\0';
			mkdir(parent, nume);
		}

		if(strcmp(comanda, "ls") == 0) {
			ls(parent);
		}

		if(strcmp(comanda, "rm") == 0) {
			char *nume = strtok(NULL, " ");
			
			if(nume[strlen(nume) - 1] == '\n')
				nume[strlen(nume) - 1] = '\0';
			if(nume[strlen(nume) - 1] == '\r')
				nume[strlen(nume) - 1] = '\0';
			rm(parent, nume);
		}

		if(strcmp(comanda, "rmdir") == 0) {
			char *nume = strtok(NULL, " ");
			
			if(nume[strlen(nume) - 1] == '\n')
				nume[strlen(nume) - 1] = '\0';
			if(nume[strlen(nume) - 1] == '\r')
				nume[strlen(nume) - 1] = '\0';
			rmdir(parent, nume);
		}

		if(strcmp(comanda, "cd") == 0) {
			char *nume = strtok(NULL, " ");
			
			if(nume[strlen(nume) - 1] == '\n')
				nume[strlen(nume) - 1] = '\0';
			if(nume[strlen(nume) - 1] == '\r')
				nume[strlen(nume) - 1] = '\0';
			cd(&parent, nume);
		}

		if(strcmp(comanda, "tree") == 0) {
			tree(parent, 0);
		}

		if(strcmp(comanda, "pwd") == 0) {
			char *s = pwd(parent);
			printf("%s\n", s);
			free(s);
		}

		if(strcmp(comanda, "stop") == 0) {
			stop(parent);
		}

		if(strcmp(comanda, "mv") == 0) {
			char *nume1 = strtok(NULL, " ");
			
			if(nume1[strlen(nume1) - 1] == '\n')
				nume1[strlen(nume1) - 1] = '\0';
			if(nume1[strlen(nume1) - 1] == '\r')
				nume1[strlen(nume1) - 1] = '\0';
			char *nume2 = strtok(NULL, " ");
			
			if(nume2[strlen(nume2) - 1] == '\n')
				nume2[strlen(nume2) - 1] = '\0';
			if(nume2[strlen(nume2) - 1] == '\r')
				nume2[strlen(nume2) - 1] = '\0';
			mv(parent, nume1, nume2);
		}
	} 
	return 0;
}