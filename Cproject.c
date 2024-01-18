#include <stdio.h>

#define Max_users 1000
#define Max_expenses 1000
#define Max_number_of_users_owedamount 4


typedef struct User {
    int user_id;
    char first_name[11];
    char last_name[11];
    float amt_spent;
} User;

 User users[Max_users] = {
    {101, "HArshada", "polshetty", 0},
    {102, "sneha", "pawar", 0},
     {103, "random", "person", 0},
    {104, "ray", "holmes", 0},
     {107, "holmes", "stan", 0},
};

typedef struct Expense {
    int expense_id;
    float amount_of_expense;
    User *paidbyuserid;
    User *sharedbyuserid[4];
} Expense;

Expense expenses[Max_expenses];
int countusers = 5;  
int countExpenses = 0;

void adduser_id(int *count);
int duplicateuser(int count);
int validuser_id(int id);
void sort();
void sortexpenses(Expense expenses[]);
void displayuser(int count);
void AddExpenses(int *countexpenses, int countusers);
int CheckValidUserId(int inputuserid, int countusers);
void displayexpense(int *countexpenses);
void DeleteExpense(int expenseid , int userid);
int amountowed(int userid);
int Amount_to_pay(int userid);
float User_balances(int userid);
int binsearch( int userid , int low ,int high );
int binsearchexpense( int userid , int low ,int high );
void settleup(int userid1 , int userid2);
void DeleteUser(int userid);

int takeinputs() {
    int ans;
    printf("\nMenu:\n");
    printf("1. Add User\n");
    printf("2. Add Expense\n");
    printf("3. Display Users\n");
    printf("4. Display Expenses\n");
    printf("5.Delete an expense\n");
    printf("6.Amount owed\n");
    printf("7.amount to pay\n");
    printf("8.User balances\n");
    printf("9.Settle Up\n");
    printf("10.Delete user id\n");
    printf("11.Exit\n");
    printf("Enter your choice: \n");
    scanf("%d", &ans);
    return ans;
}
int main() {
    int ans;
    ans = takeinputs();
    while(ans != 11)
     {
    switch(ans)
   {
    case 1 :
    {
        adduser_id(&countusers);
        break;
    }
    case 2 :
    {
         AddExpenses(&countExpenses, countusers);
         break;
    }
    case 3 :
    {
        displayuser(countusers);
        break;
    }
    case 4 :
    {
         displayexpense(&countExpenses);
         break;
    }
    case 5 :
    {
        int expenseid , userid;
            printf("Enter Expense id and User id");
            scanf("%d %d", &expenseid , &userid);
            DeleteExpense(expenseid,userid);
            break;
    }
    case 6 :
    {
            int userid;
            printf("Enter the userid ");
            scanf("%d",&userid);
            amountowed(userid);
            break;
    }
    case 7 :
    {
            int userid;
            printf("Enter the userid ");
            scanf("%d",&userid);
            Amount_to_pay(userid);
            break;
    }
    case 8 :
    {
           for(int i =0; i< countusers ;i++){
                User_balances(users[i].user_id);
            }
            break;
    }
    case 9 :
    {
            int userid1;
            int userid2;
            printf("Userid1 is payer and userid2 is reciever .Enter userid1 and userid2 :");
            scanf("%d %d",&userid1 , &userid2);
             settleup(userid1,userid2);
             break;
    }
    case 10 :
    {
         int userid;
        printf("Enter the userid ");
        scanf("%d",&userid);
        DeleteUser(userid);
        break;
    }
  }
    ans = takeinputs();
}   
return 0;
}
void adduser_id(int *count) {
    if (*count < Max_users) {
        printf("Enter the user id: ");
        scanf("%d", &users[*count].user_id);
        while (duplicateuser(*count) != 1 || !validuser_id(users[*count].user_id)) {
            if (duplicateuser(*count) == 0) {
                printf("This user id already exists\n");
                printf("Enter a different user id: ");
                scanf("%d", &users[*count].user_id);
            } else if (!validuser_id(users[*count].user_id)) {
                printf("Enter a valid 3 digit user id: ");
                scanf("%d", &users[*count].user_id);
            }
        }
        printf("Enter amount spent: ");
        scanf("%f", &users[*count].amt_spent);
        printf("Enter user first name: ");
        scanf("%s", users[*count].first_name);
        printf("Enter user last name: ");
        scanf("%s", users[*count].last_name);
        (*count)++;
        sort();
    } else {
        printf("User limit exceeded\n");
    }
}
int duplicateuser(int count)
{ int ans = 1;
    for(int i = 0 ; i < count && ans != 0 ; i++)
    { if(users[count].user_id == users[i].user_id)
        {
            ans = 0 ; 
        } }
    return ans;
}

int validuser_id(int id)
{   int ans;
    if(id > 99 && id < 999)
    {    ans = 1;
    }
    else
    {
        ans = 0;}
    return ans;
}


void sort()
{
    int j;
        User key;
        key = users[countusers -1];
        j = countusers - 1;

        while (j >= 0 && users[j].user_id > key.user_id) {

            users[j + 1] = users[j];
            for(int k = 0 ; k < countExpenses ; k++)
            {
                if(expenses[k].paidbyuserid->user_id == users[j].user_id)
                {
                    expenses[k].paidbyuserid = &users[j+1];
                }
                for (int l = 0; l < 4; l++)
                {
                    if (expenses[k].sharedbyuserid[l] == &users[j])
                    {
                        expenses[k].sharedbyuserid[l] = &users[j + 1];
                    }
                
               }
            }   
            j = j - 1;
        
    }   users[j + 1] = key;
}

void sortexpense(Expense expenses[]) {
   int i, j;
    Expense key;
    
        key = expenses[countExpenses - 1];
        j = countExpenses - 2;
        while (j >= 0 && expenses[j].expense_id > key.expense_id) 
        {
            expenses[j + 1] = expenses[j];
            j = j - 1;
        }
         expenses[j + 1]= key ;

        
    }



void displayuser(int count) {
    for (int i = 0; i < count; i++) {
        printf("%d  %f  %s %s\n", users[i].user_id, users[i].amt_spent, users[i].first_name, users[i].last_name);
    }
}

int CheckValidUserId(int inputuserid, int countusers) {
    int ans;
   if(binsearch(inputuserid , 0 , countusers - 1) == -1)
   {
    ans = 1; 
   }
   else
   {
    ans = 0;
   }
   return ans ;
}

void AddExpenses(int *countexpenses, int countusers) {
    printf("Please enter an expense id: ");
    scanf("%d", &expenses[*countexpenses].expense_id);

    while (validuser_id(expenses[*countexpenses].expense_id) == 0 || binsearchexpense(expenses[*countexpenses].expense_id,0,countExpenses -1) != -1 ) {
        printf("Enter a three-digit valid expense id: ");
        scanf("%d", &expenses[*countexpenses].expense_id);
    }
     printf("Enter the amount of the expense: ");
    scanf("%f", &expenses[*countexpenses].amount_of_expense);

    int id;int flag = 1;
    printf("Enter the user ID who paid the expense: "); 
    scanf("%d",&id);
    int m = binsearch(id,0 ,countusers - 1);
    while( m == -1)
    {
        printf("Enter a valid user id");
        scanf("%d",&id);
       m= binsearch(id,0 ,countusers - 1);
    }
    expenses[*countexpenses].paidbyuserid = &users[m];
    users[m].amt_spent = users->amt_spent + expenses[*countexpenses].amount_of_expense;
    int noofusers;
    printf("Enter the number of users who shared the expenses (up to 4): ");
    scanf("%d", &noofusers);
    while (noofusers < 0 || noofusers > 4) {
        printf("Invalid number of users. Please enter a number between 0 and 4: ");
        scanf("%d", &noofusers);
    }

    for (int j = 0; j < noofusers; j++) {
        int shareid; int flag =1;
        printf("Enter the User ID for shared user %d: ", j + 1);
        scanf("%d", &shareid);
        int i = binsearch(shareid , 0 , countusers - 1);
         while ( i == -1 || shareid == id) {
            printf("User ID does not exist. Please enter an existing user ID: ");
            scanf("%d",&shareid);
            i = binsearch(shareid , 0 , countusers - 1);
        }
        expenses[*countexpenses].sharedbyuserid[j] = &users[i];
               
}  
(*countexpenses)++;
sortexpense(expenses);
}

void displayexpense(int *countexpenses)
{
    for(int i = 0 ; i < *countexpenses ; i++)
    {
        printf(" Expense Id = %d  User Paid = %d  Name = %s ",expenses[i].expense_id, expenses[i].paidbyuserid->user_id,expenses[i].paidbyuserid->first_name);
        int j = 0;
        printf("Users who shared ");
        while( expenses[i].sharedbyuserid[j] != '\0')
        {
            printf(" %d %s ",expenses[i].sharedbyuserid[j]->user_id, expenses[i].sharedbyuserid[j]->first_name);
            j++;
        }
        printf("%d \n", j);
    }
}

void DeleteExpense(int expenseid , int userid){
    
    
    for(int i = 0; i< countExpenses ; i++){
      if(expenseid==expenses[i].expense_id ){
        if(userid==expenses[i].paidbyuserid->user_id)
        {
            for(int j = i ; j < countExpenses -1 ; j++){
                expenses[j] = expenses[j+1];
            }
            expenses[countExpenses - 1].expense_id = 0;
            expenses[countExpenses - 1].amount_of_expense = 0;
            expenses[countExpenses - 1].paidbyuserid = '\0';
            for(int k = 0 ; k < 4 ; k++)
            {
            expenses[countExpenses - 1].sharedbyuserid[k] = '\0';
            }
            countExpenses--;
        }
        else
        {
            printf("Enter correct expense and user id \n");
            scanf("%d %d" , &expenseid , &userid);
            DeleteExpense(expenseid,userid);
        }
      }
    
}
}

int amountowed(int userid)
{
    float totalomauntowed = 0;
    int i = 0;
    while(i < countusers)
    {
        float amountbyuser = 0;
        for(int j = 0 ; j < countExpenses ; j++)
        {
            if(expenses[j].paidbyuserid->user_id == userid)
            {
                int noofusers = 0;
                 while( expenses[j].sharedbyuserid[noofusers] != '\0')
                 {
                    noofusers++;
                 }
                 for(int k =0 ; k < noofusers ; k++)
                 {
                    if(users[i].user_id == expenses[j].sharedbyuserid[k]->user_id)
                    {
                        amountbyuser = amountbyuser + (expenses[j].amount_of_expense) /(noofusers + 1);
                        totalomauntowed = totalomauntowed + (expenses[j].amount_of_expense) /(noofusers + 1);
                        
                    }
                }
            }
            
        }
        printf(" %d  %s %s  %f\n", users[i].user_id,users[i].first_name , users[i].last_name , amountbyuser );
        i++;
    }
    printf("%f /n", totalomauntowed);
 return totalomauntowed;   
}    

int Amount_to_pay(int userid)
 {
    float totalamtpay = 0;
    for(int i = 0 ; i < countusers ; i++)
    {
      float  totalpaytouser = 0;
    for (int j = 0; j < countExpenses; j++)
     {
        if(users[i].user_id == expenses[j].paidbyuserid->user_id)
        {
        int noofusers = 0;
        while (expenses[j].sharedbyuserid[noofusers] != NULL)
        {
            noofusers++;
        }
        for(int k =0 ; k < noofusers ; k++)
                 {
                    if(userid == expenses[j].sharedbyuserid[k]->user_id)
                    {
                        totalpaytouser = totalpaytouser + expenses[j].amount_of_expense/(noofusers + 1);
                        totalamtpay = totalamtpay + expenses[j].amount_of_expense/(noofusers + 1);
                    }
                 }
        }
       
    }
     printf("%d %s %f \n", users[i].user_id, users[i].first_name , totalpaytouser); 
}
    printf("%f \n",totalamtpay);

 }
float User_balances(int userid){
     float totalamountowed = 0;
    for (int i = 0; i < countExpenses; i++) {
        int noofusers = 0;
        while (expenses[i].sharedbyuserid[noofusers] != NULL) {
            noofusers++;
        }
        if (expenses[i].paidbyuserid->user_id == userid) {
            for (int k = 0; k < noofusers; k++) {
            float share = expenses[i].amount_of_expense / (noofusers + 1);
            totalamountowed += share;
            }
        } else {
            for (int j = 0; j < noofusers; j++) {
                if (expenses[i].sharedbyuserid[j]->user_id == userid) {
                    totalamountowed -= expenses[i].amount_of_expense / (noofusers + 1);
                }
            }
        }
    }if(totalamountowed>0){
        printf("user with %d has to get amount %f from other users\n",userid , totalamountowed);
    }
    else if(totalamountowed<0){
        printf("User with %d has to pay %f to other users\n",userid ,(-1)*totalamountowed);
    }
    else{
        printf("Balances are settled  for %d\n",userid);
    }
    return totalamountowed;

}
//userid is payer and userid2 is reciever
void settleup(int userid1 , int userid2)
{
    float amount;
    
        for( int j = 0 ; j < countExpenses ; j++)
        {
            if( expenses[j].paidbyuserid->user_id==userid2)
            {
                int noofusers = 0;
                while( expenses[j].sharedbyuserid[noofusers] != NULL)
                {
                    noofusers++;
                }
                for(int k = 0 ; k < noofusers ; k++)
                {
                    if(expenses[j].sharedbyuserid[k]->user_id == userid1)
                    {
                        amount = expenses[j].amount_of_expense/(noofusers + 1);
                        
                    }
                }
                 printf("Expense id is %d  and userid1 should pay %f \n" , expenses[j].expense_id , amount);
            } 
       
        }
    int expenseid;
    printf("Enter the expense id you want to settle");
    scanf("%d" , &expenseid);
    int m = binsearchexpense( expenseid , 0 , countExpenses -1);
    int flag =0;
    if(m!=-1){
        while(flag==0){
            int noofusers =0;
            while(expenses[m].sharedbyuserid[noofusers]!=NULL){
                noofusers++;
            }
            for(int i =0 ; i,noofusers ;i++){
                if(expenses[m].paidbyuserid->user_id == userid2 && expenses[m].sharedbyuserid[i]->user_id == userid1)
          {
                
                 for(int K = i ; K < noofusers -1 ; K++)
                 {
                    expenses[m].sharedbyuserid[K] = expenses[m].sharedbyuserid[K+1];
                 }
                 noofusers--;
                 expenses[m].sharedbyuserid[noofusers ] = '\0';
                 expenses[m].amount_of_expense = expenses[m].amount_of_expense *(1 - 1/(noofusers + 1));
                 flag = 1;

            }
        }
    }
    }
    else{
         printf("enter correct expense id");
            scanf("%d",&expenseid);
            m = binsearchexpense( expenseid , 0 , countExpenses -1);

    }

    printf("EXPENSE SETTLED SUCCESSFULLY\n");

}


int binsearch( int userid , int low ,int high )
{
    int mid;
    int retval;
    if(low > high )
    {
        retval = -1;
    }
    else
    {
        mid = (low + high)/2;
        if(userid == users[mid].user_id)
        {
            retval = mid ;
        }
        else if ( userid < users[mid].user_id)
        {
            retval = binsearch(userid , low, mid -1);
        }
        else 
        {
            retval = binsearch(userid, mid + 1 , high);
        }
    }
    return retval;
}

int binsearchexpense( int userid , int low ,int high )

{
    int mid;
    int retval;
    if(low > high )
    {
        retval = -1;
    }
    else
    {
        mid = (low + high)/2;
        if(userid == expenses[mid].expense_id)
        {
            retval = mid ;
        }
        else if ( userid < expenses[mid].expense_id)
        {
            retval = binsearchexpense(userid , low, mid -1);
        }
        else 
        {
            retval = binsearchexpense(userid, mid + 1 , high);
        }
    }
    return retval;
}


void DeleteUser(int userid)
{
    float rembalance = User_balances(userid);
    if(rembalance == 0)
    {
         int m =binsearch(userid, 0 , countusers -1);
         for(int i = m ; i < countusers ; i++)
         {
            for (int k = 0; k < countExpenses; k++) {
                    if(expenses[k].paidbyuserid->user_id == userid)
                    {
                        DeleteExpense(expenses[k].expense_id,userid);
                    }
                    else if (expenses[k].paidbyuserid == &users[i +1]) {
                        expenses[k].paidbyuserid = &users[i];
                    }
                    int noofusers = 0;
                    while(expenses[k].sharedbyuserid[noofusers] != '\0')
                    {
                        noofusers++;
                    }
                    for(int j = 0 ; j < noofusers ; j++)
                    {
                        if(expenses[k].sharedbyuserid[j]->user_id == userid)
                        {
                             for(int x = j ; x < noofusers ; x++)
                             {
                                expenses[k].sharedbyuserid[x] = expenses[k].sharedbyuserid[x+1];
                             }
                             noofusers--;
                        }
                        else if(expenses[k].sharedbyuserid[j]->user_id == users[i + 1].user_id)
                        {
                            expenses[k].sharedbyuserid[j] = &users[i];
                            noofusers--;
                            for(int n = j+1 ; n < noofusers ; n++)
                            {
                                expenses[k].sharedbyuserid[j] = expenses[k].sharedbyuserid[j+1];
                            }
                        }

                    }
                    for(int n = noofusers ; n < 4 ; n++)
                    {
                        expenses[k].sharedbyuserid[n] = '\0';
                    }
                }
                
            users[i] = users[i+1];
        }
        countusers--;
    }
      else
      {
        printf("Settle up your balances first!! ");
         if(rembalance>0){
            printf("userid %d owes %f from other users",userid,rembalance);

        }
         else if(rembalance<0){
            printf("userid %d needs to pay %f to other users" ,userid,(-rembalance));
      }
      }
}