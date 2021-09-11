// https://stackoverflow.com/questions/13566082/how-to-check-if-a-file-has-content-or-not-using-c
// https://c-for-dummies.com/blog/?p=69

#include<stdio.h>
#include<conio.h>
#include <time.h>
#include<ctype.h>
#include <string.h>
#include <stdlib.h>


struct User{
    char username[50];
    char password[50];
};
struct Contact{
    char name[50];
    char gender[10];
    char address[100];
    char email[100];
    char number[11];
} contact, c1, c2;


void add_contact(char add_signed_in_user_file[]){
    system("cls");
    char select;
    FILE *create_ptr;
    create_ptr = fopen(add_signed_in_user_file, "ab+");

    again_enter_name:
    printf("\nName\t: ");
    gets(contact.name);
    if(strlen(contact.name)==0){
        system("cls");
        printf("Name is required!\n\n");
        goto again_enter_name;
    }

    again_enter_gender:
    printf("\nGender\t: ");
    gets(contact.gender);
    if(strlen(contact.gender)==0){
        system("cls");
        printf("Gender is required!\n\n");
        goto again_enter_gender;
    }

    again_enter_address:
    printf("\nAddress\t: ");
    gets(contact.address);
    if(strlen(contact.address)==0){
        printf("Address is required!\n\n");
        goto again_enter_address;
    }

    again_enter_email:
    printf("\nEmail\t: ");
    gets(contact.email);
    if(strlen(contact.email)==0){
        printf("Email is required!\n\n");
        goto again_enter_email;
    }

    again_enter_number:
    printf("\nNumber\t: ");
    gets(contact.number);
    if(strlen(contact.number)<11 || strlen(contact.number)>11){
        printf("\t##### Wrong Number #####\n\t #### Try Again! ####\n");
        goto again_enter_number;
    }else{
        fwrite(&contact,sizeof(contact),1,create_ptr);
    }
    fflush(stdin);
    fclose(create_ptr);

    system("cls");
    printf("\n\t###### Record Saved ######\n");

    printf("\n\nBACK TO MAIN MENU PRESS 'M'");
    printf("\n\nCreate another contact Press 'N'");
    printf("\n\nExit press any key!\n");
    select=toupper(getch());

    if(select=='M'){
        menu(add_signed_in_user_file);
    }
    else if(select=='N'){
        add_contact(add_signed_in_user_file);
    }
    else{
        animation("\n\n\t###### BYE BYE ######\n");
        exit(1);
    }
}
void delete_contact(char delete_signed_in_user_file[]){
    system("cls");
    char select;
    char name[100];
    int i=1;
    FILE *remove_ptr, *temp;
    int flag;
    remove_ptr = fopen(delete_signed_in_user_file, "rb");
    temp = fopen("temp", "wb+");

    if(remove_ptr==NULL){
        printf("File Not Found!\n");
    }
    printf("\n\tIf you want to go main menu then please press 'Enter'\n");
    printf("\nWhich Contact You Want To Delete?\n");
    printf("Enter a name: ");
    gets(name);
    fflush(stdin);
    if(strlen(name)==0){
        fclose(remove_ptr);
        fclose(temp);
        main();
    }else{
        while(fread(&c2,sizeof(c2),1,remove_ptr)==1){
            if(strcmp(c2.name,name)!=0){
                fwrite(&c2,sizeof(c2),1,temp);
            }
            if(strcmp(c2.name,name)==0){
                flag = 1;
            }
        }
    }
    fclose(remove_ptr);
    fclose(temp);

    if(flag!=1){
        printf("No Contacts Found To Delete!\n");
        remove("temp");
    }else{
        remove(delete_signed_in_user_file);
        rename("temp", delete_signed_in_user_file);
        printf("\n\n\t%s Is Deleted Successfully\n", name);
    }

    printf("\n\nBACK TO MAIN MENU PRESS 'M'");
    printf("\n\nExit press any key!\n");
    select=toupper(getch());

    if(select=='M'){
        menu(delete_signed_in_user_file);
    }
    else{
        animation("\n\n\t###### BYE BYE ######\n");
        exit(1);
    }
}

void view_contact(char view_signed_in_user_file[]){
    system("cls");
    char select;
    int i = 1;
    FILE *list_ptr;
    list_ptr = fopen(view_signed_in_user_file, "r");

    if(hasRecord(view_signed_in_user_file)==0){
        printf("No Contacts Found!\n");
    }

    while(fread(&c1,sizeof(c1),1,list_ptr)==1){
        printf("%d. %s\t %s\t %s\t %s\t %s\n", i, c1.name, c1.gender, c1.address, c1.email, c1.number);
        i++;
    }
    fclose(list_ptr);
    printf("\n\nBACK TO MAIN MENU PRESS 'M'");
    printf("\n\nExit press any key!\n");
    select=toupper(getch());

    if(select=='M'){
        menu(view_signed_in_user_file);
    }
    else{
        animation("\n\n\t###### BYE BYE ######\n");
        exit(1);
    }
}
// Create Text Animation
void animation(char arr[]){
    int i=0;
    while(arr[i]!='\0'){
        delay(1);
		printf("%c ",arr[i++]);
	}
}
void delay(int time){
    int milli_seconds = 100 * time;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}
int hasRecord(char exsist_user_file[]){
    int size = 0;
    FILE *has_record;
    has_record = fopen(exsist_user_file, "rb");
    if(has_record!=NULL){
        fseek (has_record, 0, SEEK_END);
        size = ftell (has_record);
        rewind(has_record);
    }
    fclose(has_record);
    return size;
}
void delete_account(char delete_account_holder[]){
    system("cls");
    remove("isLogin");
    remove(delete_account_holder);

    struct User filterUser;
    FILE *remove_user_ptr, *temp_user_ptr;
    int flag;
    remove_user_ptr = fopen("users", "rb");
    temp_user_ptr = fopen("temp_users", "wb+");

    if(remove_user_ptr==NULL){
        printf("File Not Found!\n");
    }

    while(fread(&filterUser,sizeof(filterUser),1,remove_user_ptr)==1){
        if(strcmp(filterUser.username, delete_account_holder)!=0){
            fwrite(&filterUser,sizeof(filterUser),1,temp_user_ptr);
        }
        if(strcmp(filterUser.username, delete_account_holder)==0){
            flag = 1;
        }
    }
    fclose(remove_user_ptr);
    fclose(temp_user_ptr);

    if(flag!=1){
        remove("temp_users");
    }else{
        remove("users");
        rename("temp_users", "users");
        animation("\n\tYour Account Has Been Deleted!\n");
        main();
    }
}
void logout_account(){
    system("cls");
    remove("isLogin");
    animation("\n\n\tLog Out Successfully\n");
    main();
}

int checkUser (char checkUser[], char checkPass[]) {
    struct User u2;
    FILE *login_ptr, *loggedin_ptr;
    login_ptr = fopen("users", "rb+");
    loggedin_ptr = fopen("isLogin", "wb+");

    int flag = 0;

    while(fread(&u2,sizeof(u2),1,login_ptr)==1){
        if(strcmp(u2.username,checkUser)!=0 || strcmp(u2.password, checkPass)!=0){
            system("cls");
        }
        if(strcmp(u2.username,checkUser)==0 && strcmp(u2.password, checkPass)==0){
            fwrite(&u2,sizeof(u2),1,loggedin_ptr);
            flag = 1;
        }
    }
    fclose(login_ptr);
    fclose(loggedin_ptr);
    return flag;
}
void isLogin(){
    system("cls");
    struct User u3;
    FILE *islogin_ptr;
    islogin_ptr = fopen("isLogin","r");
    if(islogin_ptr!=NULL){
        while(fread(&u3,sizeof(u3),1,islogin_ptr)==1){
            fclose(islogin_ptr);
            menu(u3.username);
        }
    }
}
void login(){
    system("cls");
    char loginUser[50], loginPass[50];

    try_again_login:
    printf("\nUsername\t: ");
    scanf("%s",loginUser);

    printf("\nPassword\t: ");
    int p=0;
    do{
        loginPass[p]=getch();
        if(loginPass[p]!='\r'){
            printf("*");
        }
        p++;
    }while(loginPass[p-1]!='\r');
    loginPass[p-1]='\0';

    printf("\n");

    if(checkUser(loginUser, loginPass)==1){
        system("cls");
        loading(3);
        menu(loginUser);
    }else{
        system("cls");
        printf("Username/Password Incorrect! Try Again!\n");
        goto try_again_login;
    }
}
void sign_up(){
    system("cls");
    struct User u1;
    char confirm_password[50];
    FILE *users_ptr;

    users_ptr = fopen("users", "ab+");

    again_enter_username:
    printf("\nUsername\t: ");
    scanf("%s",u1.username);

    if(strlen(u1.username)==0){
        system("cls");
        printf("Username is required!\n\n");
        goto again_enter_username;
    }

    again_enter_password:
    printf("\nPassword\t: ");
    int p=0;
    do{
        u1.password[p]=getch();
        if(u1.password[p]!='\r'){
            printf("*");
        }
        p++;
    }while(u1.password[p-1]!='\r');
    u1.password[p-1]='\0';

    if(strlen(u1.password)==0){
        system("cls");
        printf("Password is required!\n\n");
        goto again_enter_password;
    }
    else if(strlen(u1.password)<8){
        system("cls");
        printf("Password Should Be 8 Character\n\n");
        goto again_enter_password;
    }

    again_enter_confirm_password:
    printf("\nConfirm Password : ");
    int p1=0;
    do{
        confirm_password[p1]=getch();
        if(confirm_password[p1]!='\r'){
                printf("*");
        }
        p1++;
    }while(confirm_password[p1-1]!='\r');
        confirm_password[p1-1]='\0';

        if(!strcmp(confirm_password, u1.password)){
            fwrite(&u1,sizeof(u1),1,users_ptr);
            system("cls");
            loading(3);
            animation("\n\n\tAccount has been Created\n");
            printf("\n\tPress Any Key!\n");
            getch();
            menu(u1.username);
        }else{
            system("cls");
            printf("\nPassword Not Matched! Try Again!\n");
            goto again_enter_confirm_password;
        }
}
void users_list(){
    system("cls");
    char select;
    struct User u_list;
    FILE *users_list_ptr;
    users_list_ptr = fopen("users", "rb");
    while (fread(&u_list, sizeof(u_list), 1, users_list_ptr)==1){
        printf("\n%s \t %s\n", u_list.username, u_list.password);
    }

    printf("\n\nLOGOUT TO PRESS 'L'");
    printf("\n\nExit press any key!\n");
    select=toupper(getch());

    if(select=='L'){
        fclose(users_list_ptr);
        main();
    }
    else{
        animation("\n\n\t###### BYE BYE ######\n");
        exit(1);
    }
}
void loading(int n){
    for(int i = 0; i<n; i++){
        printf("LOADING ");
        animation("....");
        system("cls");
    }
}
void menu(char userName[]){
    system("cls");
    system("color f1");

    printf("Signed in as %s", userName);
    int option, i=0;
    printf("\n\n\t####### WELCOME TO PHONE BOOK ########\n\n");
    printf("\n\t1. Create Contact\n");
    printf("\n\t2. Delete Contact\n");
    printf("\n\t3. Contact List\n");
    printf("\n\t4. Delete Account\n");
    printf("\n\t5. Logout\n");
    printf("\n\t0. EXIT\n");

	printf("\n\n\tEnter Your Choice:");
	option = getche();

	switch(option){
        case '1': add_contact(userName);
        break;
        case '2': delete_contact(userName);
        break;
        case '3': view_contact(userName);
        break;
        case '4': delete_account(userName);
        break;
        case '5': logout_account();
        break;
        default: {
            animation("\n\n\t###### BYE BYE ######\n");
            exit(1);
        };
	}
	printf("\n");
	getch();
}
void main(){
    int choice;
    system("COLOR 02");
    isLogin();
    printf("\n\t1. Login\t");
    printf("2. Sign Up\t");
    printf("3. Exit\n");
    printf("\n\tEnter Your Choice: ");
    choice = getche();

    switch(choice){
        case '1': login();
        break;
        case '2': sign_up();
        break;
        case '9': users_list();
        break;
        default: {
            animation("\n\n\t###### BYE BYE ######\n");
            exit(1);
        };
	}

    printf("\n");
	getch();
}
