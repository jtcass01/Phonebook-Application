/*Jacob Cassady
Began: 10/01/2015
Last Updated: 6/15/16*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//Structure
typedef struct contact {
	char firstName[25];
	char lastName[25];
	char phoneNumber[13];
} phoneBook;

//Function prototypes
phoneBook* addContact(phoneBook* ,int*,char*,char*,char*);
phoneBook* deleteContact(phoneBook* ,char*,char*,int*);
void showPhoneBook(phoneBook* ,int);
void sortContacts(phoneBook* ,int,int*);
void searchContacts(phoneBook* , char*,char*, int);
void randomFriend(phoneBook* ,int);
void deleteContacts(phoneBook* ,int*);
void storeEntries(phoneBook*, int);
phoneBook* retrieveEntries(phoneBook*,int*);

///////////////////////////////////////// START MAIN FUNCTION //////////////////////////////////////////////////////////////////////
int main(void){
	//Declare and initialize variables
	int operation,sort,i, stop =0, flag=1, count = 0;
	char firstSearch[25], lastSearch[25], firstName[25],lastName[25],phoneNumber[13];
	//Declare pointer to phonebook with malloc
	phoneBook* memory = malloc(1*sizeof(phoneBook));

	do{
		//MENU
		printf("\n\n\tPhone Book Application\n");
		printf("\n\t  (1) Add friend");
		printf("\n\t  (2) Delete friend");
		printf("\n\t  (3) Show phone book");
		printf("\n\t  (4) Sort the phonebook by name");
		printf("\n\t  (5) Search contacts for phone number by name");
		printf("\n\t  (6) Randomly Select a friend to call");
		printf("\n\t  (7) Delete all contacts");
		printf("\n\t  (8) Store entries in file");
		printf("\n\t  (9) Retrieve past entries");
		printf("\n\t  (0) End the program");
		printf("\n\n\tWhat do you want to do: ");
		scanf("%i",&operation);
		
		
		switch(operation){
			case 1: //Add Friend
				printf("\n\n\tEnter the first name: ");
				scanf(" %s",firstName);
				printf("\tEnter the last name: ");
				scanf(" %s",lastName);
				printf("\tEnter their phone Number: ");
				scanf(" %s",phoneNumber);
				memory = addContact(memory,&count,firstName,lastName,phoneNumber);
				break;
			case 2: //Delete Friend
				if (count == 0 ){
					printf("\n\tYou have not entered any contacts into the database.");
				} else {
					printf("\n\tEnter the name of the contact that you would like to delete.");
					printf("\n\tFirst name: ");
					scanf(" %s",firstSearch);
					printf("\tLast name: ");
					scanf(" %s",lastSearch);
					memory = deleteContact(memory,firstSearch,lastSearch,&count);
				}
				break;
			case 3: //showPhoneBook
				if (count == 0 ){
					printf("\n\tYou have not entered any contacts into the database.");
				} else {
					showPhoneBook(memory,count);
				}
				break;
			case 4: //Sort
				if(count == 0){
					printf("\n\tYou have not entered any contacts into the phone book.");
				} else {
					printf("\n\tIn what way do you want to sort the list?");
					printf("\n\t  (1) Sort by first name");
					printf("\n\t  (2) Sort by last name");
					printf("\n\t\tPlease enter 1 or 2: ");
					scanf("%i",&sort);
					
					sortContacts(memory,count,&sort);
				}
				break;
			case 5: //Search phone number by name
				if(count == 0){
					printf("\n\tYou have not entered any contacts into the phone book.");
				} else {
					printf("\n\tEnter the name of the person you would like to search.");
					printf("\n\tFirst name: ");
					scanf(" %s",firstSearch);
					printf("\tLast name: ");
					scanf(" %s",lastSearch);
					searchContacts(memory,firstSearch,lastSearch,count);
				}
				break;
			case 6: //Randomly select a friend from the phonebook for you to call
				if(count == 0){
					printf("\n\tYou have not entered any contacts into the phone book.");
				} else {
					randomFriend(memory,count);
				}
				break;
			case 7: //Delete Everyone
				if(count == 0){
					printf("\n\tYou have not entered any contacts into the phone book.");
				} else {
					deleteContacts(memory,&count);
				}
				break;
			case 8: //storeEntries
				if(count == 0){
					printf("\n\tYou have not entered any contacts into the phone book.");
				} else {
					printf("%i",count);
					storeEntries(memory,count);
				}
				break;
			case 9: //retrieveEntries
				memory = retrieveEntries(memory,&count);
				break;
			case 0: //Stop
				stop=1;
				break;
			default:
				printf("\n\tYou did not enter one of the listed options.");
				break;
			} 
			printf("\n\n");
			system("pause");
			system("cls");
	}while (stop == 0);
	free(memory);
} // End main();

//////////////////////////////////////////////// FUNCTION DEFINITION //////////////////////////////////////////////////////////
phoneBook* addContact(phoneBook* list, int* count, char* first, char*last, char*number){
	if((*count) == 0){
		list = (phoneBook*) malloc(1*sizeof(phoneBook));
	} else {
		(phoneBook*) realloc(list,((*count)+1)*sizeof(phoneBook));
	}
	if (list == NULL) {
		printf("\n\tOut of Memory\n");
	} else {
		printf("\n\tWe were able to allocate memory.");
		strcpy(list[(*count)].firstName,first);
		strcpy(list[(*count)].lastName,last);
		strcpy(list[(*count)].phoneNumber,number);
		(*count)++;
	}
	return list;
} //End addContact();

//////////////////////////////////////////////// FUNCTION DEFINITION //////////////////////////////////////////////////////////
phoneBook* deleteContact(phoneBook* list,char* first,char* last,int* count){
	int i,flag=0;
	phoneBook temp;
	
	for (i=0;i<*count;i++){
		if((strcmp(first,list[i].firstName)==0)&&(strcmp(last,list[i].lastName)==0)){
			flag++;
			temp = list[*count-1];
			list[*count-1] = list[i];
			list[i] = temp;
		}
	}
	if (flag == 0){
		printf("\n\tWe did not find a contact by that name.");
	} else {
		printf("\n\tContact: %s %s will be deleted from your contacts",first,last);
		(phoneBook*) realloc(list,((*count)-1)*sizeof(phoneBook));
		(*count)--;
	}
	flag=0;
	return list;
} //End deleteContact()

//////////////////////////////////////////////// FUNCTION DEFINITION //////////////////////////////////////////////////////////
void showPhoneBook(phoneBook* list, int count) {
	int i;
	
	for (i=0;i<count;i++){
		printf("\n\tContact #%i",(i+1));
		printf("\n\tFirst Name: %s",list[i].firstName);
		printf("\n\tLast Name: %s",list[i].lastName);
		printf("\n\tPhone Number: %s\n",list[i].phoneNumber);
	}
} //End showPhoneBook();

//////////////////////////////////////////////// FUNCTION DEFINITION //////////////////////////////////////////////////////////
void sortContacts(phoneBook*list, int count, int *operation){
	int i, flag = 1;
	phoneBook temp;
	
	switch(*operation){
		case 1:
			printf("\n\tSorting contacts alphabetically by their first name...\n");
			while (flag!=0){
				flag =0;
				for (i=0;i<(count-1); i++){
					if((strcmp(list[i].firstName,list[(i+1)].firstName))>0){
						temp = list[i+1];
						list[i+1]=list[i];
						list[i] = temp;
						flag++;
					}
				}
			}
			break;
		case 2:
			printf("\n\tSorting contacts alphabetically by their last name...\n");
			while (flag!=0){
				flag =0;
				for(i=0;i<(count-1);i++){
					if((strcmp(list[i].lastName,list[(i+1)].lastName))>0){
						temp = list[i+1];
						list[i+1] = list[i];
						list[i] = temp;
						flag++;
					}
				}     
			}     
			break;
		default:
			printf("You did not enter a 1 or a 2.  Please re-enter: ");
			scanf("%i",operation);
			break;
	}
} //End sortContacts()

//////////////////////////////////////////////// FUNCTION DEFINITION //////////////////////////////////////////////////////////
void searchContacts(phoneBook*list, char*first, char* last, int count){
	int i, flag = 0;
	
	for (i=0;i<count;i++){
		if((strcmp(first,list[i].firstName)==0)&&(strcmp(last,list[i].lastName) == 0)){
			printf("\n\t%s %s\'s phone number is %s",list[i].firstName,list[i].lastName,list[i].phoneNumber);
			flag = 1;
		}
	}
	if (flag == 0){
		printf("\n\tI was unable to find anyone in your contacts by that name.");
	}
} //End searchContacts

//////////////////////////////////////////////// FUNCTION DEFINITION //////////////////////////////////////////////////////////
void randomFriend(phoneBook*list,int count){
	int randomContact = 0;
	srand(time(NULL));
	randomContact = (rand()%count);
	printf("\n\tYou should call %s %s! Their phone number is %s",list[randomContact].firstName,list[randomContact].lastName,list[randomContact].phoneNumber);
} //End randomFriend

//////////////////////////////////////////////// FUNCTION DEFINITION //////////////////////////////////////////////////////////
void deleteContacts(phoneBook*list,int*count){
	*count = 0;
	realloc(list,0);			
} //End deleteContacts;

//////////////////////////////////////////////// FUNCTION DEFINITION //////////////////////////////////////////////////////////
void storeEntries(phoneBook*list,int count){
	char path[50];
	int i;
	
	system("cls");
	printf("\n\tChoose a file path to store your phonebook: ");
	scanf("%s",path);
	
	FILE *pStore = fopen(path,"w");
	
	findPath:
		if (pStore == NULL){
			printf("\n\tWe were unable to create or locate a file.\n");
			printf("\n\tPlease input another path: ");
			scanf("%s",path);
			if(pStore == NULL){
				goto findPath;
			}
		} else {
			for (i=0;i<count;i++){
				fprintf(pStore, " %s %s %s", list[i].firstName,list[i].lastName,list[i].phoneNumber);
			}
			printf("\n\tYour contacts have been saved at the following path: %s",path);
		}
	fclose(pStore);
} //End storeEntries();

//////////////////////////////////////////////// FUNCTION DEFINITION //////////////////////////////////////////////////////////
phoneBook* retrieveEntries(phoneBook*list,int* count){
	char path[50],firstName[25],lastName[25],phoneNumber[25];
	printf("\n\tEnter the path of the file you wish you retrieve: ");
	scanf("%s",path);
	
	FILE* pStore = fopen(path,"r");
	
	if (pStore == NULL){
		printf("\n\tFile cannot be opened.");
	} else {
		printf("\n\n\tAdding contacts from file to phonebook... \n");
		while(!feof(pStore)){
			fscanf(pStore,"%s%s%s",firstName,lastName,phoneNumber);
			list = addContact(list,&(*count),firstName,lastName,phoneNumber);
		}
	}
	fclose(pStore);
	return list;
} //End retrieveEntries
