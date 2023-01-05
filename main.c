#define true 1 /* Old Habbit :) */
#define false 0 /* Old Habbit :) */
#include "StructHeader.h"

int main()
{

    User* dummy = malloc(sizeof (User));
    dummy->Next = NULL;

    char* Username = NULL;
    char* Password = NULL;
    int LoginFlag = 0;

    do
    {
        system("cls");

        char* command;
        printf("Enter our command:\n");
        command = GetInput(Both);

        if(strcmpi(command,"exit") == 0)
        {
            FILE* useroutput = fopen("Users.txt","w");
            FILE* postsoutput = fopen("Posts.txt","w");
            User* current = dummy->Next;
            while (current != NULL)
            {
                fprintf(useroutput,"%s %s\n",current->Username,current->Password);
                Post* posts = current->PostsDummy;
                if(posts == NULL)
                {
                    current = current->Next;
                    continue;
                }
                posts = posts->Next;
                while(posts != NULL)
                {
                    fprintf(postsoutput,"%s %s %d\n",posts->Text,posts->SenderID,posts->Likes);
                    posts = posts->Next;
                }
                fprintf(postsoutput,"%s\n","=======================");
                current = current->Next;
            }

            fclose(useroutput);
            fclose(postsoutput);

            system("cls");
            return Quit();
        }

        else if(strcmpi(command,"help") == 0)
        {
            printf("%s\n\n","Welcome to Ut Tooti \x1\n"
                   "Hope you're not finding it too hard to use :)\n\n"

                   "Caution: In this app, CAPITAL LETTERS and small letters are considered equal in commands, but not user names or passwords\n\n"

                   "Here's the list of commands you can use:\n\n"

                   "1. signup <new user name> <password>\n"
                   "example: signup hamid 12#t\n"
                   "description: creates an account for you\n\n"

                   "2. login <user name> <password>\n"
                   "example: login erfan pnh2880\n"
                   "description: gets connected to your account if already exists\n\n"

                   "3. post <text>\n"
                   "example: post Argentina is the winner of the world cup!!\n"
                   "description: posts what you give it\n\n"

                   "4. like <user name> <post ID>\n"
                   "example: like Navid 7\n"
                   "description: it's used to like a post\n\n"

                   "5. logout\n"
                   "example: logout\n"
                   "description: logs out of your account\n\n"

                   "6. delete <post_id>\n"
                   "example: delete 3\n"
                   "description: deletes the post of yours which has <post_id> as its id\n\n"

                   "7. info\n"
                   "example: info\n"
                   "description: shows your information, including user name, password, and all your posts and number of their \x3likes\x3\n\n"

                   "8. find_user <username>\n"
                   "example: find_user darya23\n"
                   "description: shows a user's information, including user name and all your posts and number of their \x3likes\x3. no password will be shown\n\n"

                   "9. help\n"
                   "example: help\n"
                   "description: shows this text you're currently reading :)\n\n"

                   "10. exit\n"
                   "example: exit\n"
                   "description: exits UT Tooti. Will miss you :(\n\n"

                   "Hope that was helpful\n"
                    "\x5 bye \x5");

            system("pause");
        }

        if(strcmpi(command,"signup") == 0)
        {
            if(LoginFlag == 0)
            {
                Username = GetInput(Both);
                Password = GetInput(Both); /* take username and password */
                if(!SignUpUser(dummy,Username,Password))
                {
                    DelayedStringPrint("Failed to signup user\nThis could be due to lack of memory or repeated username",4,Show,"Try again in",0,0);
                    system("cls");
                    fflush(stdin);
                    free(command);
                    continue;
                }
                system("cls");
                printf("Welcome...\n\nYour username: %s\nYour password: %s",Username,Password);
                sleep(4);
                LoginFlag = 1;
            }
            else
            {
                DelayedStringPrint("You're already logged in\nLog out first",3,Hide,"",1,1);
            }

        }

        else if(strcmpi(command,"logout") == 0)
        {
            if(LoginFlag == 1)
            {
                free(Username);
                free(Password);
                LoginFlag = 0;
                DelayedStringPrint("Logged out successfully...",2,Hide,"",1,1);
            }
            else
            {
                DelayedStringPrint("You're not logged in yet\nLog in or sign up first",3,Hide,"",1,1);
            }

        }

        else if(strcmpi(command,"login") == 0)
        {
            if(LoginFlag == 0)
            {
                Username = GetInput(Both);
                Password = GetInput(Both);
                User* user = FindUser(dummy,Username,CurrentElement);
                if(user == NULL)
                {
                    DelayedStringPrint("USERNAME NOT FOUND",3,Show,"Try a correct username in",1,1);
                    free(Username);
                    free(Password);
                    system("cls");
                    fflush(stdin);
                    free(command);
                    continue;
                }
                if(strcmpi(user->Password,Password) != 0)
                {
                    DelayedStringPrint("WRONG PASSWORD",3,Show,"Try again with the correct password in",1,1);
                    free(Username);
                    free(Password);
                    system("cls");
                    fflush(stdin);
                    free(command);
                    continue;
                }
                LoginFlag = 1;
                system("cls");
                printf("Welcome...\n\nYour username: %s\nYour password: %s",Username,Password);
                sleep(4);
                LoginFlag = 1;
            }
            else
            {
                DelayedStringPrint("You're already logged in\nLog out first",2,Hide,"",1,1);
            }
        }

        else if(strcmpi(command,"post") == 0)
        {
            if(LoginFlag == 1)
            {
                char* text = GetInput(Enter);
                if(!SendPost(FindUser(dummy,Username,CurrentElement)->PostsDummy,Username,text))
                {
                    DelayedStringPrint("Failed to send post\nThis could be due to lack of memory",4,Show,"Try again in",0,0);
                }
                else
                {
                    DelayedStringPrint("Post sent successfully",3,Hide,"",1,1);
                }
            }
            else
            {
                DelayedStringPrint("You're not logged in yet\nLog in or sign up first",3,Hide,"",1,1);
            }
        }

        else if(strcmpi(command,"info") == 0)
        {
            if(LoginFlag == 1)
            {
                PrintUser(FindUser(dummy,Username,CurrentElement),ShowPassword);
                puts("");
                system("pause");
            }
            else
            {
                DelayedStringPrint("You're not logged in yet\nLog in or sign up first",3,Hide,"",1,1);
            }
        }

        else if(strcmpi(command,"find_user") == 0)
        {
            if(LoginFlag == 1)
            {
                char* un = GetInput(Both);
                User* us = FindUser(dummy,un,CurrentElement);
                if(us == NULL)
                {
                    DelayedStringPrint("Username not found...",3,Hide,"",1,1);
                }
                else
                {
                    PrintUser(us,HidePassword);
                    puts("\n");
                    system("pause");
                }
            }
            else
            {
                DelayedStringPrint("You're not logged in yet\nLog in or sign up first",3,Hide,"",1,1);
            }
        }

        if(strcmpi(command,"delete") == 0)
        {
            if(LoginFlag == 1)
            {
                char* c_id = GetInput(Both);
                int id = atoi(c_id);
                Post* post = FindPost(FindUser(dummy,Username,CurrentElement)->PostsDummy,id,CurrentElement);
                if(post == NULL)
                {
                    DelayedStringPrint("Post ID not found...",3,Hide,"",1,1);
                }
                else
                {
                    DeletePost(FindUser(dummy,Username,CurrentElement)->PostsDummy,id);
                    DelayedStringPrint("Post Removed Successfully",3,Hide,"",1,1);
                }
            }
            else
            {
                DelayedStringPrint("You're not logged in yet\nLog in or sign up first",3,Hide,"",1,1);
            }
        }

        if(strcmpi(command,"like") == 0)
        {
            if(LoginFlag == 1)
            {
                char* likeuser = GetInput(Both);
                char* likepostid = GetInput(Both);
                User* user = FindUser(dummy,likeuser,CurrentElement);
                if(user == NULL)
                {
                    DelayedStringPrint("Username not found...",3,Hide,"",1,1);
                    free(likeuser);
                    free(likepostid);
                    fflush(stdin);
                    system("cls");
                    free(command);
                    continue;
                }
                /* This part is to check if the user has already liked that post */
                Post* pst = FindUser(dummy,Username,CurrentElement)->LikedPostsDummy;
                if(pst != NULL)
                {
                    int flag = 0;
                    while(pst->Next != NULL)
                    {
                        char* temp = GeneratePostPK(likeuser,atoi(likepostid));
                        if(strcmp(pst->Next->PrimaryKey,temp) == 0)
                        {
                            DelayedStringPrint("Post Already Liked...",3,Hide,"",1,1);
                            free(likeuser);
                            free(likepostid);
                            fflush(stdin);
                            system("cls");
                            flag = 1;
                            break;
                        }
                        pst = pst->Next;
                        free(temp);
                    }
                    if(flag)
                    {
                        free(command);
                        continue;
                    }
                }
                if(!LikePost(dummy,likeuser,atoi(likepostid)))
                {
                    DelayedStringPrint("Post not found...",3,Hide,"",1,1);
                }
                else
                {
                    SendToLikedPosts(FindUser(dummy,Username,CurrentElement)->LikedPostsDummy,likeuser,atoi(likepostid));
                    DelayedStringPrint("Post liked Successfully",3,Hide,"",1,1);
                }
            }
            else
            {
                DelayedStringPrint("You're not logged in yet\nLog in or sign up first",3,Hide,"",1,1);
            }
        }



        system("cls");
        fflush(stdin);
        /* Just to be safe :)  The GetInput is a function I coded using scanf with %c format specifier.
           So far, there hasn't been any bugs in it but I tend to keep it from any possible crashes.
           That's why I flush the buffer before using the function again
        */

        free(command); /* after checking what commands says, there is no longer any need for its old data.
                          So it's best to free the memory afterwards to prevent memory leak.
                       */

    }
    while(true);

    return 0;
}
