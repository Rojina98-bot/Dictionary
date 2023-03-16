#include"Node.h"
//trie* getNewNode();
//trie* insert(trie *head,string str);
trie* search(trie *head,string str);
void getPrefixHelp(trie *node,string str,vector<string>& result_word,vector<string>& result_meaning);
void adding_to_file(string word,string meaning,string pos1);
void searchPrefix(trie *head)
{
    system("cls");
    vector<string>result_word;
    vector<string>result_meaning;
    
    if (head == NULL) {//exception condition
        cout<<"empty trie"<<endl;
        return;
    }
    trie *t;
    string key;
    char choice;
    cout<<"\t\t   ###########################"<<"\t\t ?:new key  |  b:main page"<<endl;
    cout<<"\t\t(  )\tEnter the key"<<endl;
    cout<<"\t\t / ###########################"<<"\t\t\t enter everthing in lower alphabet and no symbols"<<endl;
    cin>>key;
    t=search(head,key);
    if(t==NULL)
    {
        cout<<"the prefix does not exist"<<endl;
        return;
    }
    getPrefixHelp(t,key,result_word,result_meaning);
    cout<<endl<<endl;
    cout<<setw(20)<<"WORD:"<<"\t\t\t"<<"MEANING:"<<endl<<endl;
    for(int i=0;i<result_word.size();i++)
    {
        
        cout<<setw(20)<<result_word[i]<<"\t\t\t"<<result_meaning[i]<<endl;

    }
    cout<<endl<<endl;
    cout<<"?\t\t\t\t?:new key  |  b:main page"<<endl;
    cin>>choice;
    if(choice=='?')
    {
        searchPrefix(head);//use this function unless user tells to go to main page
    }
    else if(choice=='b')
    {
        return;
    }
}
void searchWord(trie *head)//getprefix does the work for all, it is a superset
{
    system("cls");
    if (head == NULL) {//exception condition
        cout<<"empty trie"<<endl;
        return;
    }
    trie *key;
    string str;
    char choice;
    
    cout<<"\t\t  ###########################"<<"\t\t ?:new key  |  b:main page"<<endl;
    cout<<"\t\t(  )\tenter the key"<<endl;
    cout<<"\t\t / ###########################"<<"\t\t\t enter everthing in lower alphabet and no symbols"<<endl;
    cin>>str;
    key=search(head,str);
    if(key==NULL)
    {
        cout<<"the word does not exist"<<endl;
        return;
    }
    cout<<endl;
    cout<<"WORD:\t\t MEANING:"<<endl;
    cout<<key->word<<"\t\t"<<key->meaning<<endl;
    cout<<endl<<endl;
    cout<<"?\b\b\b\b?:new key  |  b:main page"<<endl;
    cin>>choice;
    if(choice=='?')
    {
        searchPrefix(head);
    }
    else if(choice=='b')
    {
        return;
    }

}
void insertDesign()
{
    system("cls");
    string word,meaning,pos1;
    char choice;
    cout<<"######################"<<"\t\t ?:new key  |  b:main page"<<endl;
    cout<<"\tWORD"<<endl;
    cout<<"######################"<<"\t\t\t enter everthing in lower alphabet and no symbols"<<endl<<endl;
    cin.ignore();
    getline(cin,word);
    cout<<endl<<endl;
    cout<<"######################"<<endl;
    cout<<"\t MEANING"<<endl;
    cout<<"######################"<<endl<<endl;
    cin.ignore();//to ignore newline in stream
    getline(cin,meaning);
    cout<<endl<<endl;
    cout<<"######################"<<endl;
    cout<<" part of speech "<<endl;
    cout<<"######################"<<endl<<endl;
    cin>>pos1;
    adding_to_file(word,meaning,pos1);//this is void
    cout<<endl;
    cout<<"?\b\b\b\b?:new key  |  b:main page"<<endl;
    cin>>choice;
    if(choice=='?')
    {
        insertDesign();
    }
    else if(choice=='b')
    {
        return;
    }
}
char coverPage()
{
    char userInput;
    system("cls");
    cout << "\033[32m"; // Set text color to green
    cout<<"\t\t\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<" \t\t\t\t\t\tOXFORD DICTIONARY "<<endl;
    cout<<"\t\t\t\t+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl<<endl<<endl<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t |\t\t's' for search for prefix    |"<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t |\t\t 'i' for insert\t\t     |"<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t |\t\t 'w' for word\t\t     |"<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t |\t\t'e' for exit \t\t     |"<<endl;
    cout<<"\t\t *********************************************"<<endl<<endl<<endl;
    cout<<"CHOICE"<<endl;
    cout<<"||||||||||||||||||||||||||||||"<<endl;
    cin>>userInput;
    cout<<"||||||||||||||||||||||||||||||"<<endl;
    return userInput;
}
void firstPage(trie *head)
{
    char userInput;
    userInput=coverPage();//for the first time, not keeping in loop
    //while(1){
    /*do{
    system("cls");
    cout << "\033[32m"; // Set text color to green
    cout<<"\t\t\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<" \t\t\t\t\t\tOXFORD DICTIONARY "<<endl;
    cout<<"\t\t\t\t+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl<<endl<<endl<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t |\t\t's' for search for prefix    |"<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t |\t\t 'i' for insert\t\t     |"<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t |\t\t 'w' for word\t\t     |"<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t |\t\t'e' for exit \t\t     |"<<endl;
    cout<<"\t\t *********************************************"<<endl<<endl<<endl;
    cout<<"CHOICE"<<endl;
    cout<<"||||||||||||||||||||||||||||||"<<endl;
    cin>>userInput;
    cout<<"||||||||||||||||||||||||||||||"<<endl;*/
    while(userInput!='e')
    {
    switch(userInput)
    {
    
        case 's':
        { 
       
            system("cls");
            searchPrefix(head);
            break;
        }
        case 'i':
        {
            system("cls");
            insertDesign();
            break;


        }
        case 'w':
        {
            system("cls");
            searchWord(head);
            break;
        }
        //case 'e':
        //exit(0);

        default:
        {
        cout<<"invalid";
        break;
        }
        
    }
    userInput=coverPage();//this is called until 'e' exit is pressed
    }//while(userInput!='e');


}
