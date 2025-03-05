#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

struct date_format{
    short day, month, year;
};

struct transaction_format{
    float amount;
    char type[16];
    char category[16];
    char description[100];
    struct date_format date;
};

struct affiliates_format{
    char tag[40];
    char first_name[20];
    char second_name[20];
    char activity_domain[16];
    char phone[11];
};

struct account{
    int transaction_index;
    float account_balace;
    char tag[20];
    char first_name[16];
    char second_name[16];
    char password[32];
    char type[16];
    char phone_number[11];
    struct date_format birthday;
    struct affiliates_format affiliates[128];
    struct transaction_format transaction[512];
}account_database[50];

int accounts_number = 0;
short current_account = -1; // Updated after login/register
gpointer main_menu; // Used to store main window
gpointer last_window; // Used to store last oepened window

void show_account_interface();

// Open an error window and print the string from gchar *message parameter
void show_error(gchar *message){
    GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(NULL),GTK_DIALOG_MODAL , GTK_MESSAGE_ERROR,GTK_BUTTONS_CLOSE,"%s", message);
    gtk_dialog_run(GTK_DIALOG(error_dialog));
    gtk_widget_destroy(error_dialog);
}

// Close the window get through gpointer data paramater
void close_window(GtkWidget *widget, gpointer data) {
    gtk_widget_destroy(data);
}

// Show the window get through gpointer data paramater
void show_window(GtkWidget *widget, gpointer data){
    gtk_widget_show(data);
}

void import_database(){

}

void export_database(){

}

////////////////////
//
//  Check functions
//
////////////////////

int account_tag_is_used(const gchar *checked_tag){
    for(int index = 0; index < accounts_number; index++)
        if(strcmp(checked_tag, account_database[index].tag))
            return 1;
    return 0;
}

int string_have_only_letters(const gchar *checked_string){
    char normal_string[20];
    g_strlcpy(normal_string, checked_string, sizeof(normal_string)); // copy the char allocated dynamic in normal one to be checked
    for(int index = 0; index < strlen(normal_string); index++)
        if(normal_string[index] < 'A' || normal_string[index] > 'z')
            return 0;
    return 1;
}

int string_have_only_digits_extended(const gchar *checked_string){ // extended means can have also . and , for float numbers
    char normal_string[11];
    g_strlcpy(normal_string, checked_string, sizeof(normal_string)); // copy the char allocated dynamic in normal one to be checked
    for(int index = 0; index < strlen(normal_string); index++)
        if((normal_string[index] < '0' || normal_string[index] > '9') && normal_string[index] != ',' && normal_string[index] != '.')
            return 0;
    return 1;
}

int string_have_only_digits(const gchar *checked_string){
    char normal_string[11];
    g_strlcpy(normal_string, checked_string, sizeof(normal_string)); // copy the char allocated dynamic in normal one to be checked
    for(int index = 0; index < strlen(normal_string); index++)
        if(normal_string[index] < '0' || normal_string[index] > '9')
            return 0;
    return 1;
}

int password_differ(const gchar *password1, const gchar *password2){
    if(strcmp(password1, password2))
        return 1;
    return 0;
}

int available_account_type(const gchar *checked_account_type){
    if(strcmp(checked_account_type, "savings") == 0)
        return 1;
    else if(strcmp(checked_account_type, "checking") == 0)
        return 1;
    else if(strcmp(checked_account_type, "credit") == 0)
        return 1;
    return 0;
}

short check_available_date_with_bypass(const gchar *day, const gchar *month, const gchar *year){ // bypass means you can leave the fields blank

    if(!string_have_only_digits(day)){
        show_error("The day need to be a number!");
        return 1;
    }
    else if(!string_have_only_digits(month)){
        show_error("The month need to be a number!");
        return 1;
    }
    else if(!string_have_only_digits(year)){
        show_error("The year need to be a number!");
        return 1;
    }

    guint64 int_day = g_ascii_strtoull(day, NULL, 10); // transform a string formatted from digits to an integer
    guint64 int_month = g_ascii_strtoull(month, NULL, 10); // this function is from gtk input options
    guint64 int_year = g_ascii_strtoull(year, NULL, 10);

    if(strlen(year) != 0) {
        if (int_year < 1700) {
            show_error("The entered year is far too far away!");
            return 1;
        } else if (int_year > 2005) {
            show_error("You do not have a minimum age to open an account!");
            return 1;
        }
    }

    if(strlen(month) != 0) {
        if (int_month < 1 || int_month > 12) {
            show_error("The month does not exist!");
            return 1;
        }
    }

    if(strlen(day) != 0) {
        if (int_day < 1 || int_day > 31) {
            show_error("The day does not exist!");
            return 1;
        } else if (int_day == 31 &&
                   (int_month == 2 || int_month == 4 || int_month == 6 || int_month == 9 || int_month == 11)) {
            show_error("The month has only 30 days!");
            return 1;
        } else if (int_day == 30 && int_month == 2) {
            show_error("The month can have a maximum of 29 days!");
            return 1;
        } else if (int_day == 29 && int_month == 2 && int_year % 4 != 0) {
            show_error("The year February has a maximum of 28 days!");
            return 1;
        }
    }
    return 0;
}

short check_available_date(const gchar *day, const gchar *month, const gchar *year){ // available date means it is valid inside the calendar

    if(!string_have_only_digits(day)){
        show_error("The day need to be a number!");
        return 1;
    }
    else if(!string_have_only_digits(month)){
        show_error("The month need to be a number!");
        return 1;
    }
    else if(!string_have_only_digits(year)){
        show_error("The year need to be a number!");
        return 1;
    }

    guint64 int_day = g_ascii_strtoull(day, NULL, 10); // transform a string formatted from digits to an integer
    guint64 int_month = g_ascii_strtoull(month, NULL, 10); // this function is from gtk input options
    guint64 int_year = g_ascii_strtoull(year, NULL, 10);

    if(int_year < 1700){
        show_error("The entered year is far too far away!");
        return 1;
    }
    else if(int_year > 2005){
        show_error("You do not have a minimum age to open an account!");
        return 1;
    }

    if(int_month < 1 || int_month > 12){
        show_error("The month does not exist!");
        return 1;
    }

    if(int_day < 1 || int_day > 31){
        show_error("The day does not exist!");
        return 1;
    }
    else if(int_day == 31 && (int_month == 2 || int_month == 4 || int_month == 6 || int_month == 9 || int_month == 11) ){
        show_error("The month has only 30 days!");
        return 1;
    }
    else if(int_day == 30 && int_month == 2){
        show_error("The month can have a maximum of 29 days!");
        return 1;
    }
    else if(int_day == 29 && int_month == 2 && int_year % 4 != 0){
        show_error("The year February has a maximum of 28 days!");
        return 1;
    }
    return 0;
}

// Check if the date inputed is valid and if the latest transaction is earlier than current one
int check_date_for_transaction(const gchar *day, const gchar *month, const gchar *year){
    if(!string_have_only_digits(day)){
        show_error("The day need to be a number!");
        return 1;}
    else if(!string_have_only_digits(month)){
        show_error("The month need to be a number!");
        return 1;}
    else if(!string_have_only_digits(year)){
        show_error("The year need to be a number!");
        return 1;}

    guint64 int_day = g_ascii_strtoull(day, NULL, 10);
    guint64 int_month = g_ascii_strtoull(month, NULL, 10);
    guint64 int_year = g_ascii_strtoull(year, NULL, 10);
    int flag = 0; // This will be used to know if we are in the same year/month as the previous transaction.
    int last_transaction_index = account_database[current_account].transaction_index;

    if(int_year < 1700){
        show_error("There were no banks this year. People kept currency hidden in their homes!");
        return 1;}
    else if(int_year > 9999){
        show_error("The year format is invalid. It must have a maximum of 4 digits!");
        return 1;}
    else if(last_transaction_index > 0 && int_year < account_database[current_account].transaction[last_transaction_index].date.year){ // Initially we check if there is a previous transaction
        show_error("The last transaction was recorded in the future. You can't introduce now something that has already happened.");
        return 1;}
    else if(last_transaction_index > 0 && int_year ==account_database[current_account].transaction[last_transaction_index].date.year) // If we are in the same year we set the flag to 1
            flag = 1;

    if(int_month < 1 || int_month > 12){
        show_error("This month does not exist!");
        return 1;}
    else if(flag == 1 && int_month < account_database[current_account].transaction[last_transaction_index].date.month) {// The flag is 1 so we automatically have a previous transaction
        show_error("The last transaction was recorded in the future. You can't introduce now something that has already happened.");
        return 1;}
    else if(flag == 1 && int_month > account_database[current_account].transaction[last_transaction_index].date.month) // Check if we are in the same month as the previous transaction
            flag = 0;

    if(int_day < 1 || int_day > 31){
        show_error("This day does not exist!");
        return 1;}
    else if(int_day == 31 && (int_month == 2 || int_month == 4 || int_month == 6 || int_month == 9 || int_month == 11) ){
        show_error("This month has only 30 days!");
        return 1;}
    else if(int_day == 30 && int_month == 2){
        show_error("This month can have a maximum of 29 days!");
        return 1;}
    else if(int_day == 29 && int_month == 2 && int_year % 4 != 0){
        show_error("This year February has a maximum of 28 days!");
        return 1;}
    else if(flag == 1 && int_day < account_database[current_account].transaction[last_transaction_index].date.day){ // If the months and years are the same, we cannot take a day smaller than the previous one.
        show_error("The last transaction was recorded in the future. You can't introduce now something that has already happened.");
        return 1;}
    return 0;
}

////////////////////
//
//  Services functions
//
////////////////////


// Manage the inputs from new trancation interface and work with them inside the memory to add money in user account
// GtkApplication *app - isn't used inside the function but is required from previous gtk function call
// gpointer data - provides the location inside the memory for inptus
void add_to_balance(GtkWidget *widget, gpointer data){

    GtkWidget **entries = (GtkWidget **)data;
    const gchar *amount = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *description = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    const gchar *day = gtk_entry_get_text(GTK_ENTRY(entries[2]));
    const gchar *month = gtk_entry_get_text(GTK_ENTRY(entries[3]));
    const gchar *year = gtk_entry_get_text(GTK_ENTRY(entries[4]));

    short error_encountered = 0;
    gdouble money_amount;

    if(strlen(amount) == 0){
        error_encountered = 1;
        show_error("You need to add an amount!");}

    if(string_have_only_digits_extended(amount))
        money_amount = g_ascii_strtod(amount, NULL); // this function transorm an string of digits into a double number
    else{
        error_encountered = 1;
        show_error("The amount isn't a number!");}

    if(strlen(description) > 99){
        error_encountered = 1;
        show_error("The description is too long! You can use maximum 100 characters.");}

    if(!check_date_for_transaction(day, month, year) && error_encountered == 0){

        guint64 int_day = g_ascii_strtoull(day, NULL, 10);
        guint64 int_month = g_ascii_strtoull(month, NULL, 10);
        guint64 int_year = g_ascii_strtoull(year, NULL, 10);

        account_database[current_account].transaction_index ++;
        int last_transaction_index = account_database[current_account].transaction_index;

        account_database[current_account].account_balace += money_amount;
        account_database[current_account].transaction[last_transaction_index].date.day = int_day;
        account_database[current_account].transaction[last_transaction_index].date.month = int_month;
        account_database[current_account].transaction[last_transaction_index].date.year = int_year;
        account_database[current_account].transaction[last_transaction_index].amount = money_amount;
        strcpy(account_database[current_account].transaction[last_transaction_index].description, description);
        strcpy(account_database[current_account].transaction[last_transaction_index].category, "deposit");

        gtk_widget_destroy(last_window);
        show_account_interface();
    }
}

// Manage the inputs from new trancation interface and work with them inside the memory to remove money from user account
// GtkApplication *app - isn't used inside the function but is required from previous gtk function call
// gpointer data - provides the location inside the memory for inptus
void withdraw_from_balance(GtkWidget *widget, gpointer data){

    GtkWidget **entries = (GtkWidget **)data;
    const gchar *amount = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *description = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    const gchar *day = gtk_entry_get_text(GTK_ENTRY(entries[2]));
    const gchar *month = gtk_entry_get_text(GTK_ENTRY(entries[3]));
    const gchar *year = gtk_entry_get_text(GTK_ENTRY(entries[4]));

    short error_encountered = 0;
    gdouble money_amount;

    if(strlen(amount) == 0){
        error_encountered = 1;
        show_error("You need to add an amount!");}

    if(string_have_only_digits_extended(amount)) {
        money_amount = g_ascii_strtod(amount, NULL); // this function transorm an string of digits into a double number
        if (account_database[current_account].account_balace < money_amount){
            error_encountered = 1;
            show_error("You have a lower balance than inputed number!");}}
    else{
        error_encountered = 1;
        show_error("The amount isn't a number!");}

    if(strlen(description) > 99){
        error_encountered = 1;
        show_error("The description is too long! You can use maximum 100 characters.");}

    if(!check_date_for_transaction(day, month, year) && error_encountered == 0){

        guint64 int_day = g_ascii_strtoull(day, NULL, 10);
        guint64 int_month = g_ascii_strtoull(month, NULL, 10);
        guint64 int_year = g_ascii_strtoull(year, NULL, 10);

        account_database[current_account].transaction_index ++;
        int last_transaction_index = account_database[current_account].transaction_index;

        account_database[current_account].account_balace -= money_amount;
        account_database[current_account].transaction[last_transaction_index].date.day = int_day;
        account_database[current_account].transaction[last_transaction_index].date.month = int_month;
        account_database[current_account].transaction[last_transaction_index].date.year = int_year;
        account_database[current_account].transaction[last_transaction_index].amount = money_amount;
        strcpy(account_database[current_account].transaction[last_transaction_index].description, description);
        strcpy(account_database[current_account].transaction[last_transaction_index].category, "withdraw");

        gtk_widget_destroy(last_window);
        show_account_interface();

    }
}

// Manage the inputs from new trancation interface and work with them inside the memory to transfer money from user account to another one
// GtkApplication *app - isn't used inside the function but is required from previous gtk function call
// gpointer data - provides the location inside the memory for inptus
void make_a_transaction(GtkWidget *widget, gpointer data){

    GtkWidget **entries = (GtkWidget **)data;
    const gchar *amount = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *description = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    const gchar *day = gtk_entry_get_text(GTK_ENTRY(entries[2]));
    const gchar *month = gtk_entry_get_text(GTK_ENTRY(entries[3]));
    const gchar *year = gtk_entry_get_text(GTK_ENTRY(entries[4]));

    short error_encountered = 0;
    gdouble money_amount;

    if(strlen(amount) == 0){
        error_encountered = 1;
        show_error("You need to add an amount!");}

    if(string_have_only_digits_extended(amount)) {
        money_amount = g_ascii_strtod(amount, NULL); // this function transorm an string of digits into a double number
        if (account_database[current_account].account_balace < money_amount){
            error_encountered = 1;
            show_error("You have a lower balance than inputed number!");}}
    else{
        error_encountered = 1;
        show_error("The amount isn't a number!");}

    if(strlen(description) > 99){
        error_encountered = 1;
        show_error("The description is too long! You can use maximum 100 characters.");}

    if(!check_date_for_transaction(day, month, year) && error_encountered == 0){

        guint64 int_day = g_ascii_strtoull(day, NULL, 10);
        guint64 int_month = g_ascii_strtoull(month, NULL, 10);
        guint64 int_year = g_ascii_strtoull(year, NULL, 10);

        account_database[current_account].transaction_index ++;
        int last_transaction_index = account_database[current_account].transaction_index;

        account_database[current_account].account_balace -= money_amount;
        account_database[current_account].transaction[last_transaction_index].date.day = int_day;
        account_database[current_account].transaction[last_transaction_index].date.month = int_month;
        account_database[current_account].transaction[last_transaction_index].date.year = int_year;
        account_database[current_account].transaction[last_transaction_index].amount = money_amount;
        strcpy(account_database[current_account].transaction[last_transaction_index].description, description);
        strcpy(account_database[current_account].transaction[last_transaction_index].category, "transaction");

        gtk_widget_destroy(last_window);
        show_account_interface();

    }
}

// Manage the inputs from new trancation interface and work with them inside the memory to remove money from user account
// GtkApplication *app - isn't used inside the function but is required from previous gtk function call
// gpointer data - provides the location inside the memory for inptus
void make_a_payment(GtkWidget *widget, gpointer data){

    GtkWidget **entries = (GtkWidget **)data;
    const gchar *amount = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *description = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    const gchar *day = gtk_entry_get_text(GTK_ENTRY(entries[2]));
    const gchar *month = gtk_entry_get_text(GTK_ENTRY(entries[3]));
    const gchar *year = gtk_entry_get_text(GTK_ENTRY(entries[4]));

    short error_encountered = 0;
    gdouble money_amount;

    if(strlen(amount) == 0){
        error_encountered = 1;
        show_error("You need to add an amount!");}

    if(string_have_only_digits_extended(amount)) {
        money_amount = g_ascii_strtod(amount, NULL);
        if (account_database[current_account].account_balace < money_amount){
            error_encountered = 1;
            show_error("You have a lower balance than inputed number!");}}
    else{
        error_encountered = 1;
        show_error("The amount isn't a number!");
    }

    if(strlen(description) > 99)
        show_error("The description is too long! You can use maximum 100 characters.");

    if(!check_date_for_transaction(day, month, year) && error_encountered == 0){

        guint64 int_day = g_ascii_strtoull(day, NULL, 10);
        guint64 int_month = g_ascii_strtoull(month, NULL, 10);
        guint64 int_year = g_ascii_strtoull(year, NULL, 10);

        account_database[current_account].transaction_index ++;
        int last_transaction_index = account_database[current_account].transaction_index;

        account_database[current_account].account_balace -= money_amount;
        account_database[current_account].transaction[last_transaction_index].date.day = int_day;
        account_database[current_account].transaction[last_transaction_index].date.month = int_month;
        account_database[current_account].transaction[last_transaction_index].date.year = int_year;
        account_database[current_account].transaction[last_transaction_index].amount = money_amount;
        strcpy(account_database[current_account].transaction[last_transaction_index].description, description);
        strcpy(account_database[current_account].transaction[last_transaction_index].category, "payment");

        gtk_widget_destroy(last_window);
        show_account_interface();

    }
}

void logout_from_an_account(){
    current_account = -1;
}

void delete_an_account(){
    for(int index = current_account; index < accounts_number; index++)
        account_database[index] = account_database[index + 1];
    current_account = -1;
    accounts_number--;
}

// Manage the inputs from edit interface
// GtkApplication *app - isn't used inside the function but is required from previous gtk function call
// gpointer data - provides the location inside the memory for inptus
void edit_an_account(GtkApplication *app, gpointer data){

    GtkWidget **entries = (GtkWidget **)data;
    const gchar *current_password = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *account_password = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    const gchar *account_password2 = gtk_entry_get_text(GTK_ENTRY(entries[2]));
    const gchar *account_type = gtk_entry_get_text(GTK_ENTRY(entries[3]));
    const gchar *user_phone_number = gtk_entry_get_text(GTK_ENTRY(entries[4]));
    const gchar *user_first_name = gtk_entry_get_text(GTK_ENTRY(entries[5]));
    const gchar *user_second_name = gtk_entry_get_text(GTK_ENTRY(entries[6]));
    const gchar *user_birthday_day = gtk_entry_get_text(GTK_ENTRY(entries[7]));
    const gchar *user_birthday_month = gtk_entry_get_text(GTK_ENTRY(entries[8]));
    const gchar *user_birthday_year = gtk_entry_get_text(GTK_ENTRY(entries[9]));

    short error_encountered = 0;
    if(password_differ(current_password, account_database[current_account].password)){
        error_encountered = 1;
        show_error("Wrong password!");
    }
    else if(strlen(account_password) > 32){
        error_encountered = 1;
        show_error("Inputed password is too long or dosen't exist! Maximum 32 characters.");}
    else if(strlen(account_password2) > 32){
        show_error("Inputed confirm password is too long  or dosen't exist! Maximum 32 characters.");}
    else if(strlen(account_type) > 16){
        error_encountered = 1;
        show_error("Inputed account type is too long or dosen't exist!\nAvailable types: savings, checking, credit.");}
    else if(strlen(user_phone_number) > 11){
        error_encountered = 1;
        show_error("Inputed phone number type is too long or dosen't exist! Maximum 11 characters.");}
    else if(strlen(user_first_name) > 16){
        error_encountered = 1;
        show_error("Inputed first name type is too long or dosen't exist! Maximum 16 characters.");}
    else if(strlen(user_second_name) > 16){
        error_encountered = 1;
        show_error("Inputed second name type is too long or dosen't exist! Maximum 16 characters.");}
    else if(password_differ(account_password, account_password2)){
        error_encountered = 1;
        show_error("The passwords do not match!");}
    else if(!available_account_type(account_type) && strlen(account_type) != 0){
        error_encountered = 1;
        show_error("Invalid account type!\nAvailable types: savings, checking, credit.");}
    else if(!string_have_only_letters(user_first_name)){
        error_encountered = 1;
        show_error("First name can have only letters!");}
    else if(!string_have_only_letters(user_second_name)){
        error_encountered = 1;
        show_error("Second name can have only letters!");}
    else if(!string_have_only_digits(user_phone_number)){
        error_encountered = 1;
        show_error("Phone number can have only digits!");}
    else
        error_encountered = check_available_date_with_bypass(user_birthday_day, user_birthday_month, user_birthday_year);

    if(!error_encountered){
        if(strlen(account_password) != 0)
            g_strlcpy(account_database[current_account].password, account_password, sizeof(account_database[current_account].password));
        if(strlen(account_type) != 0)
            g_strlcpy(account_database[current_account].type, account_type, sizeof(account_database[current_account].type));
        if(strlen(user_phone_number) != 0)
            g_strlcpy(account_database[current_account].phone_number, user_phone_number, sizeof(account_database[current_account].phone_number));
        if(strlen(user_first_name) != 0)
            g_strlcpy(account_database[current_account].first_name, user_first_name, sizeof(account_database[current_account].first_name));
        if(strlen(user_second_name) != 0 )
            g_strlcpy(account_database[current_account].second_name, user_second_name, sizeof(account_database[current_account].second_name));

        guint64 int_day = g_ascii_strtoull(user_birthday_day, NULL, 10);
        guint64 int_month = g_ascii_strtoull(user_birthday_month, NULL, 10);
        guint64 int_year = g_ascii_strtoull(user_birthday_year, NULL, 10);

        if(strlen(user_birthday_day) != 0 )
            account_database[current_account].birthday.day = int_day;
        if(strlen(user_birthday_month) != 0 )
            account_database[current_account].birthday.month = int_month;
        if(strlen(user_birthday_year) != 0 )
            account_database[current_account].birthday.year = int_year;

        gtk_widget_destroy(last_window);
        show_account_interface();
    }
}


// Manage the inputs from login interface
// GtkApplication *app - isn't used inside the function but is required from previous gtk function call
// gpointer data - provides the location inside the memory for inptus
void login_to_an_account(GtkApplication *app, gpointer data){

    GtkWidget **entries = (GtkWidget **)data;
    const gchar *account_tag = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *account_password = gtk_entry_get_text(GTK_ENTRY(entries[1]));

    short error_encountered = 0;
    if(strlen(account_tag) > 20){
        error_encountered = 1;
        show_error("Account tag input is too long! Maximum 20 characters.");}
    else if(strlen(account_password) > 32){
        error_encountered = 1;
        show_error("Inputed password is too long! Maximum 32 characters.");}
    else if(!string_have_only_letters(account_tag)){
        error_encountered = 1;
        show_error("Account tag can have only letters!");}

    if(!error_encountered){ // Check the usertag in databse only if respect the input conditions
        short account_found = 0;
        for(int index = 0; index < accounts_number; index++){
            if(strcmp(account_tag, account_database[index].tag) == 0){
                account_found = 1;
                if(strcmp(account_password,account_database[index].password) == 0) {
                    current_account = index;
                    gtk_widget_destroy(last_window);
                    show_account_interface();
                }
                else
                    show_error("Wrong password!");
            }
        }
        if(!account_found)
            show_error("Account tag can't be find!");
    }
}

// Manage the inputs from register interface
// GtkApplication *app - isn't used inside the function but is required from previous gtk function call
// gpointer data - provides the location inside the memory for inptus
void create_an_account(GtkApplication *app, gpointer data){

    GtkWidget **entries = (GtkWidget **)data;
    const gchar *account_tag = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *account_password = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    const gchar *account_password2 = gtk_entry_get_text(GTK_ENTRY(entries[2]));
    const gchar *account_type = gtk_entry_get_text(GTK_ENTRY(entries[3]));
    const gchar *user_phone_number = gtk_entry_get_text(GTK_ENTRY(entries[4]));
    const gchar *user_first_name = gtk_entry_get_text(GTK_ENTRY(entries[5]));
    const gchar *user_second_name = gtk_entry_get_text(GTK_ENTRY(entries[6]));
    const gchar *user_birthday_day = gtk_entry_get_text(GTK_ENTRY(entries[7]));
    const gchar *user_birthday_month = gtk_entry_get_text(GTK_ENTRY(entries[8]));
    const gchar *user_birthday_year = gtk_entry_get_text(GTK_ENTRY(entries[9]));

    short error_encountered = 0;
    if(accounts_number >= 50){
        show_error("The database can't support more users!");
        error_encountered = 1;}
    else if(strlen(account_tag) > 20 || strlen(account_tag) == 0){
        error_encountered = 1;
        show_error("Account tag input is too long or dosen't exist! Maximum 20 characters.");}
    else if(strlen(account_password) > 32 || strlen(account_password) == 0){
        error_encountered = 1;
        show_error("Inputed password is too long or dosen't exist! Maximum 32 characters.");}
    else if(strlen(account_password2) > 32 || strlen(account_password2) == 0){
        show_error("Inputed confirm password is too long  or dosen't exist! Maximum 32 characters.");}
    else if(strlen(account_type) > 16 || strlen(account_type) == 0){
        error_encountered = 1;
        show_error("Inputed account type is too long or dosen't exist!\nAvailable types: savings, checking, credit.");}
    else if(strlen(user_phone_number) > 11 || strlen(user_phone_number) == 0){
        error_encountered = 1;
        show_error("Inputed phone number type is too long or dosen't exist! Maximum 11 characters.");}
    else if(strlen(user_first_name) > 16 || strlen(user_first_name) == 0){
        error_encountered = 1;
        show_error("Inputed first name type is too long or dosen't exist! Maximum 16 characters.");}
    else if(strlen(user_second_name) > 16 || strlen(user_second_name) == 0 ){
        error_encountered = 1;
        show_error("Inputed second name type is too long or dosen't exist! Maximum 16 characters.");}
    else if(account_tag_is_used(account_tag)){
        error_encountered = 1;
        show_error("This account tag is already in use!");}
    else if(!string_have_only_letters(account_tag)){
        error_encountered = 1;
        show_error("Account tag can have only letters!");}
    else if(password_differ(account_password, account_password2)){
        error_encountered = 1;
        show_error("The passwords do not match!");}
    else if(!available_account_type(account_type)){
        error_encountered = 1;
        show_error("Invalid account type!\nAvailable types: savings, checking, credit.");}
    else if(!string_have_only_letters(user_first_name)){
        error_encountered = 1;
        show_error("First name can have only letters!");}
    else if(!string_have_only_letters(user_second_name)){
        error_encountered = 1;
        show_error("Second name can have only letters!");}
    else if(!string_have_only_digits(user_phone_number)){
        error_encountered = 1;
        show_error("Phone number can have only digits!");}
    else
        error_encountered = check_available_date(user_birthday_day, user_birthday_month, user_birthday_year);

    if(!error_encountered){
        g_strlcpy(account_database[accounts_number].tag, account_tag, sizeof(account_database[accounts_number].tag));
        g_strlcpy(account_database[accounts_number].password, account_password, sizeof(account_database[accounts_number].password));
        g_strlcpy(account_database[accounts_number].type, account_type, sizeof(account_database[accounts_number].type));
        g_strlcpy(account_database[accounts_number].phone_number, user_phone_number, sizeof(account_database[accounts_number].phone_number));
        g_strlcpy(account_database[accounts_number].first_name, user_first_name, sizeof(account_database[accounts_number].first_name));
        g_strlcpy(account_database[accounts_number].second_name, user_second_name, sizeof(account_database[accounts_number].second_name));

        guint64 int_day = g_ascii_strtoull(user_birthday_day, NULL, 10);
        guint64 int_month = g_ascii_strtoull(user_birthday_month, NULL, 10);
        guint64 int_year = g_ascii_strtoull(user_birthday_year, NULL, 10);

        account_database[accounts_number].birthday.day = int_day;
        account_database[accounts_number].birthday.month = int_month;
        account_database[accounts_number].birthday.year = int_year;

        current_account = accounts_number;
        accounts_number++;
        gtk_widget_destroy(last_window);
        show_account_interface();
    }
}

////////////////////
//
//  User interface functions
//
////////////////////

// Create the new transaction interface with fields for informations and a menu which transaction types.
// GtkWidget *widget - isn't used inside the function but is required from previous gtk function call
// gpointer data - provides the window from which this menu was opened to hide it
void show_new_transaction_interface(GtkWidget *widget, gpointer data) {

    GtkWidget *new_transaction_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    last_window = new_transaction_window;
    gtk_window_set_default_icon_from_file("images/bank_icon.png", NULL);
    gtk_window_set_title(GTK_WINDOW(new_transaction_window), "GentlixBank - Application");
    gtk_window_set_default_size(GTK_WINDOW(new_transaction_window), 800, 1000);
    gtk_window_maximize(GTK_WINDOW(new_transaction_window));

    GtkWidget *overlay_main_box = gtk_overlay_new();
    gtk_container_add(GTK_CONTAINER(new_transaction_window), overlay_main_box);
    GtkWidget *image_app_background = gtk_image_new_from_file("images/app_background.png");
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_main_box), image_app_background);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_set_spacing(GTK_BOX(main_box), 50);
    gtk_container_set_border_width(GTK_CONTAINER(main_box), 50);

    GtkWidget *upper_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_size_request(GTK_WIDGET(upper_box), -1, 400);
    gtk_box_pack_start(GTK_BOX(main_box), upper_box, TRUE, TRUE, 0);

    GtkWidget *overlay_upper_box = gtk_overlay_new();
    gtk_box_pack_start(GTK_BOX(upper_box), overlay_upper_box, TRUE, TRUE, 0);
    GtkWidget *image_background = gtk_image_new_from_file("images/transactions_background.png");
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_upper_box), image_background);

    GtkWidget *content_box_for_upper_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *image_logo = gtk_image_new_from_file("images/bank_logo.png");
    gtk_box_pack_start(GTK_BOX(content_box_for_upper_box), image_logo, FALSE, FALSE, 65);

    GtkWidget *text_title = gtk_label_new("New Transaction");
    const gchar *css_title_format = "label { font-size: 72px; color: #000000; font-weight: bold; }";
    GtkCssProvider *title_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(title_provider, css_title_format, -1, NULL);
    GtkStyleContext *title_context = gtk_widget_get_style_context(text_title);
    gtk_style_context_add_provider(title_context, GTK_STYLE_PROVIDER(title_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(title_provider);

    gtk_box_pack_start(GTK_BOX(content_box_for_upper_box), text_title, FALSE, FALSE, 10);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_upper_box), content_box_for_upper_box);

    GtkWidget *lower_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 30);
    gtk_widget_set_size_request(GTK_WIDGET(lower_box), -1, 500);
    gtk_box_pack_start(GTK_BOX(main_box), lower_box, TRUE, TRUE, 0);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_size_request(grid, 100, -1);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 20);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 20);
    gtk_box_pack_start(GTK_BOX(lower_box), grid, FALSE, FALSE, 30);

    GtkWidget **entries = (GtkWidget **)g_malloc(6 * sizeof(GtkWidget *));

    PangoAttrList *attr_list_text = pango_attr_list_new();
    PangoAttribute *attr_size_text = pango_attr_size_new(35 * PANGO_SCALE);
    pango_attr_list_insert(attr_list_text, attr_size_text);
    PangoAttribute *attr_bold_text = pango_attr_weight_new(PANGO_WEIGHT_SEMIBOLD);
    pango_attr_list_insert(attr_list_text, attr_bold_text);

    PangoAttrList *attr_list_entry = pango_attr_list_new();
    PangoAttribute *attr_size_entry = pango_attr_size_new(25 * PANGO_SCALE);
    pango_attr_list_insert(attr_list_entry, attr_size_entry);

    GtkWidget *username_label = gtk_label_new("                            Amount:");
    gtk_label_set_attributes(GTK_LABEL(username_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), username_label, 0, 0, 1, 1);

    entries[0] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[0]), "Enter money amount");
    gtk_entry_set_attributes(GTK_ENTRY(entries[0]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[0]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[0], 1, 0, 1, 1);

    GtkWidget *password_label = gtk_label_new("                          Description:");
    gtk_label_set_attributes(GTK_LABEL(password_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), password_label, 0, 1, 1, 1);

    entries[1] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[1]), "Enter transfer's description");
    gtk_entry_set_attributes(GTK_ENTRY(entries[1]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[1]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[1], 1, 1, 1, 1);

    GtkWidget *day_birthday_label = gtk_label_new("                   Transaction Day:");
    gtk_label_set_attributes(GTK_LABEL(day_birthday_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), day_birthday_label, 2, 0, 1, 1);

    entries[2] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[2]), "Enter the day");
    gtk_entry_set_attributes(GTK_ENTRY(entries[2]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[2]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[2], 3, 0, 1, 1);

    GtkWidget *month_birthday_label = gtk_label_new("                  Transaction Month:");
    gtk_label_set_attributes(GTK_LABEL(month_birthday_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), month_birthday_label, 2, 1, 1, 1);

    entries[3] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[3]), "Enter the month");
    gtk_entry_set_attributes(GTK_ENTRY(entries[3]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[3]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[3], 3, 1, 1, 1);

    GtkWidget *year_birthday_label = gtk_label_new("                  Transaction Year:");
    gtk_label_set_attributes(GTK_LABEL(year_birthday_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), year_birthday_label, 2, 2, 1, 1);

    entries[4] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[4]), "Enter the year");
    gtk_entry_set_attributes(GTK_ENTRY(entries[4]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[4]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[4], 3, 2, 1, 1);

    GtkWidget *deposit_button = gtk_button_new_with_label("Deposit");
    GtkWidget *withdraw_button = gtk_button_new_with_label("Withdraw");
    GtkWidget *pay_button = gtk_button_new_with_label("Pay");
    GtkWidget *transfer_button = gtk_button_new_with_label("Transfer");
    GtkWidget *cancel_button = gtk_button_new_with_label("Cancel");

    const char *css = "label { font-size: 45px; font-weight: 600; }";
    GtkCssProvider *buttons_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(buttons_provider, css, -1, NULL);
    GtkWidget *buttons[] = {deposit_button, withdraw_button, pay_button, transfer_button, cancel_button};
    for (int i = 0; i < G_N_ELEMENTS(buttons); i++) {
        GtkWidget *label = gtk_bin_get_child(GTK_BIN(buttons[i]));
        gtk_style_context_add_provider(gtk_widget_get_style_context(label), GTK_STYLE_PROVIDER(buttons_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        if (i == 0) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(add_to_balance), entries);
        } else if (i == 1) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(withdraw_from_balance), entries);
        } else if (i == 2) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(make_a_payment), entries);
        } else if (i == 3) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(make_a_transaction), entries);
        } else if (i == 4) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(show_account_interface), NULL);
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(close_window), new_transaction_window);
        }
        gtk_box_pack_start(GTK_BOX(lower_box), buttons[i], TRUE, TRUE, 0);
    }
    g_object_unref(buttons_provider);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_main_box), main_box);
    gtk_widget_show_all(GTK_WIDGET(new_transaction_window));
    gtk_widget_hide(data);
}

// Create the all transactions interface and a grid table with all transactions for logged user
// GtkWidget *widget - isn't used inside the function but is required from previous gtk function call
// gpointer data - provides the window from which this menu was opened to hide it
void show_all_transactions_interface(GtkWidget *widget, gpointer data) {

    GtkWidget *all_transactions_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    last_window = all_transactions_window;
    gtk_window_set_default_icon_from_file("images/bank_icon.png", NULL);
    gtk_window_set_title(GTK_WINDOW(all_transactions_window), "GentlixBank - Application");
    gtk_window_set_default_size(GTK_WINDOW(all_transactions_window), 800, 1000);
    gtk_window_maximize(GTK_WINDOW(all_transactions_window));

    GtkWidget *overlay_main_box = gtk_overlay_new();
    gtk_container_add(GTK_CONTAINER(all_transactions_window), overlay_main_box);
    GtkWidget *image_app_background = gtk_image_new_from_file("images/app_background.png");
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_main_box), image_app_background);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_set_spacing(GTK_BOX(main_box), 50);
    gtk_container_set_border_width(GTK_CONTAINER(main_box), 50);

    GtkWidget *upper_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_size_request(GTK_WIDGET(upper_box), -1, 400);
    gtk_box_pack_start(GTK_BOX(main_box), upper_box, TRUE, TRUE, 0);

    GtkWidget *overlay_upper_box = gtk_overlay_new();
    gtk_box_pack_start(GTK_BOX(upper_box), overlay_upper_box, TRUE, TRUE, 0);
    GtkWidget *image_background = gtk_image_new_from_file("images/history_background.png");
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_upper_box), image_background);

    GtkWidget *content_box_for_upper_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *image_logo = gtk_image_new_from_file("images/bank_logo.png");
    gtk_box_pack_start(GTK_BOX(content_box_for_upper_box), image_logo, FALSE, FALSE, 55);

    GtkWidget *text_title = gtk_label_new("Your Transactions");
    const gchar *css_title_format = "label { font-size: 72px; color: #000000; font-weight: bold; }";
    GtkCssProvider *title_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(title_provider, css_title_format, -1, NULL);
    GtkStyleContext *title_context = gtk_widget_get_style_context(text_title);
    gtk_style_context_add_provider(title_context, GTK_STYLE_PROVIDER(title_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(title_provider);

    gtk_box_pack_start(GTK_BOX(content_box_for_upper_box), text_title, FALSE, FALSE, 10);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_upper_box), content_box_for_upper_box);

    GtkWidget *lower_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 30);
    gtk_widget_set_size_request(GTK_WIDGET(lower_box), -1, 400);
    gtk_box_pack_start(GTK_BOX(main_box), lower_box, TRUE, TRUE, 0);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_size_request(grid, 100, -1);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 20);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 50);
    gtk_box_pack_start(GTK_BOX(lower_box), grid, FALSE, FALSE, 30);

    PangoAttrList *attr_list_title = pango_attr_list_new();
    PangoAttribute *attr_size_title = pango_attr_size_new(35 * PANGO_SCALE);
    pango_attr_list_insert(attr_list_title, attr_size_title);
    PangoAttribute *attr_bold_title = pango_attr_weight_new(PANGO_WEIGHT_SEMIBOLD);
    pango_attr_list_insert(attr_list_title, attr_bold_title);

    PangoAttrList *attr_list_content = pango_attr_list_new();
    PangoAttribute *attr_size_content = pango_attr_size_new(25 * PANGO_SCALE);
    pango_attr_list_insert(attr_list_content, attr_size_content);

    GtkWidget *number_label = gtk_label_new("                                             Number");
    gtk_label_set_attributes(GTK_LABEL(number_label), attr_list_title);
    gtk_grid_attach(GTK_GRID(grid), number_label, 0, 0, 1, 1);

    GtkWidget *type_label = gtk_label_new("Type");
    gtk_label_set_attributes(GTK_LABEL(type_label), attr_list_title);
    gtk_grid_attach(GTK_GRID(grid), type_label, 1, 0, 1, 1);

    GtkWidget *amount_label = gtk_label_new("Amount");
    gtk_label_set_attributes(GTK_LABEL(amount_label), attr_list_title);
    gtk_grid_attach(GTK_GRID(grid), amount_label, 2, 0, 1, 1);

    GtkWidget *day_label = gtk_label_new("Day");
    gtk_label_set_attributes(GTK_LABEL(day_label), attr_list_title);
    gtk_grid_attach(GTK_GRID(grid), day_label, 3, 0, 1, 1);

    GtkWidget *month_label = gtk_label_new("Month");
    gtk_label_set_attributes(GTK_LABEL(month_label), attr_list_title);
    gtk_grid_attach(GTK_GRID(grid), month_label, 4, 0, 1, 1);

    GtkWidget *year_label = gtk_label_new("Year");
    gtk_label_set_attributes(GTK_LABEL(year_label), attr_list_title);
    gtk_grid_attach(GTK_GRID(grid), year_label, 5, 0, 1, 1);

    GtkWidget *description_label = gtk_label_new("Description");
    gtk_label_set_attributes(GTK_LABEL(description_label), attr_list_title);
    gtk_grid_attach(GTK_GRID(grid), description_label, 6, 0, 1, 1);

    for(int index = 1; index <= account_database[current_account].transaction_index; index++)
    {
        gchar *print_number_format = g_strdup_printf("                                                             %d.", index);
        GtkWidget *number_text = gtk_label_new(NULL);
        gtk_label_set_text(GTK_LABEL(number_text), print_number_format);
        gtk_label_set_attributes(GTK_LABEL(number_text), attr_list_content);
        gtk_grid_attach(GTK_GRID(grid), number_text, 0, index, 1, 1);
        g_free(print_number_format);

        gchar *print_type_format = g_strdup_printf("%s", account_database[current_account].transaction[index].category);
        GtkWidget *type_text = gtk_label_new(NULL);
        gtk_label_set_text(GTK_LABEL(type_text), print_type_format);
        gtk_label_set_attributes(GTK_LABEL(type_text), attr_list_content);
        gtk_grid_attach(GTK_GRID(grid), type_text, 1, index, 1, 1);
        g_free(print_type_format);

        gchar *print_amount_format = g_strdup_printf("%.2f$", account_database[current_account].transaction[index].amount);
        GtkWidget *amount_text = gtk_label_new(NULL);
        gtk_label_set_text(GTK_LABEL(amount_text), print_amount_format);
        gtk_label_set_attributes(GTK_LABEL(amount_text), attr_list_content);
        gtk_grid_attach(GTK_GRID(grid), amount_text, 2, index, 1, 1);
        g_free(print_amount_format);

        gchar *print_day_format = g_strdup_printf("%d", account_database[current_account].transaction[index].date.day);
        GtkWidget *day_text = gtk_label_new(NULL);
        gtk_label_set_text(GTK_LABEL(day_text), print_day_format);
        gtk_label_set_attributes(GTK_LABEL(day_text), attr_list_content);
        gtk_grid_attach(GTK_GRID(grid), day_text, 3, index, 1, 1);
        g_free(print_day_format);

        gchar *print_month_format = g_strdup_printf("%d", account_database[current_account].transaction[index].date.month);
        GtkWidget *month_text = gtk_label_new(NULL);
        gtk_label_set_text(GTK_LABEL(month_text), print_month_format);
        gtk_label_set_attributes(GTK_LABEL(month_text), attr_list_content);
        gtk_grid_attach(GTK_GRID(grid), month_text, 4, index, 1, 1);
        g_free(print_month_format);

        gchar *print_year_format = g_strdup_printf("%d", account_database[current_account].transaction[index].date.year);
        GtkWidget *year_text = gtk_label_new(NULL);
        gtk_label_set_text(GTK_LABEL(year_text), print_year_format);
        gtk_label_set_attributes(GTK_LABEL(year_text), attr_list_content);
        gtk_grid_attach(GTK_GRID(grid), year_text, 5, index, 1, 1);
        g_free(print_year_format);

        gchar *print_description_format = g_strdup_printf("%s", account_database[current_account].transaction[index].description);
        GtkWidget *description_text = gtk_label_new(NULL);
        gtk_label_set_text(GTK_LABEL(description_text), print_description_format);
        gtk_label_set_attributes(GTK_LABEL(description_text), attr_list_content);
        gtk_grid_attach(GTK_GRID(grid), description_text, 6, index, 1, 1);
        g_free(print_description_format);
    }

    GtkWidget *close_button = gtk_button_new_with_label("Close");

    const char *css = "label { font-size: 45px; font-weight: 600; }";
    GtkCssProvider *buttons_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(buttons_provider, css, -1, NULL);
    GtkWidget *buttons[] = {close_button};
    for (int i = 0; i < G_N_ELEMENTS(buttons); i++) {
        GtkWidget *label = gtk_bin_get_child(GTK_BIN(buttons[i]));
        gtk_style_context_add_provider(gtk_widget_get_style_context(label), GTK_STYLE_PROVIDER(buttons_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        if (i == 0) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(show_account_interface), NULL);
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(close_window), all_transactions_window);
        }
        gtk_box_pack_start(GTK_BOX(lower_box), buttons[i], FALSE, TRUE, 0);
    }
    g_object_unref(buttons_provider);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_main_box), main_box);
    gtk_widget_show_all(GTK_WIDGET(all_transactions_window));
    gtk_widget_hide(data);
}

// Create the edit account interface with same fields as register one but blank ones are ignored
// GtkWidget *widget - isn't used inside the function but is required from previous gtk function call
// gpointer data - provides the window from which this menu was opened to hide it
void show_edit_account_interface(GtkApplication *app, gpointer data){

    GtkWidget *edit_account_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    last_window = edit_account_window;
    gtk_window_set_default_icon_from_file("images/bank_icon.png", NULL);
    gtk_window_set_title(GTK_WINDOW(edit_account_window), "GentlixBank - Application");
    gtk_window_set_default_size(GTK_WINDOW(edit_account_window), 800, 1000);
    gtk_window_maximize(GTK_WINDOW(edit_account_window));

    GtkWidget *overlay_main_box = gtk_overlay_new();
    gtk_container_add(GTK_CONTAINER(edit_account_window), overlay_main_box);
    GtkWidget *image_app_background = gtk_image_new_from_file("images/app_background.png");
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_main_box), image_app_background);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_set_spacing(GTK_BOX(main_box), 50);
    gtk_container_set_border_width(GTK_CONTAINER(main_box), 50);

    GtkWidget *upper_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_size_request(GTK_WIDGET(upper_box), -1, 320);
    gtk_box_pack_start(GTK_BOX(main_box), upper_box, TRUE, TRUE, 0);

    GtkWidget *overlay_upper_box = gtk_overlay_new();
    gtk_box_pack_start(GTK_BOX(upper_box), overlay_upper_box, TRUE, TRUE, 0);
    GtkWidget *image_background = gtk_image_new_from_file("images/main_background.jpg");
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_upper_box), image_background);

    GtkWidget *content_box_for_upper_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *image_logo = gtk_image_new_from_file("images/bank_logo.png");
    gtk_box_pack_start(GTK_BOX(content_box_for_upper_box), image_logo, FALSE, FALSE, 50);

    GtkWidget *text_title = gtk_label_new("Edit account");
    const gchar *css_title_format = "label { font-size: 72px; color: #FFDFAF; font-weight: bold; }";
    GtkCssProvider *title_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(title_provider, css_title_format, -1, NULL);
    GtkStyleContext *title_context = gtk_widget_get_style_context(text_title);
    gtk_style_context_add_provider(title_context, GTK_STYLE_PROVIDER(title_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(title_provider);

    GtkWidget *text_subtitle = gtk_label_new("Update your account details!\nBlank ones will be ignored.");
    const gchar *css_subtitle_format = "label { font-size: 48px; color: #E7E7E7; font-weight: 550; }";
    GtkCssProvider *subtitle_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(subtitle_provider, css_subtitle_format, -1, NULL);
    GtkStyleContext *subtitle_context = gtk_widget_get_style_context(text_subtitle);
    gtk_style_context_add_provider(subtitle_context, GTK_STYLE_PROVIDER(subtitle_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(subtitle_provider);

    gtk_box_pack_start(GTK_BOX(content_box_for_upper_box), text_title, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(content_box_for_upper_box), text_subtitle, FALSE, FALSE, 0);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_upper_box), content_box_for_upper_box);

    GtkWidget *lower_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 30);
    gtk_widget_set_size_request(GTK_WIDGET(lower_box), -1, 400);
    gtk_box_pack_start(GTK_BOX(main_box), lower_box, TRUE, TRUE, 0);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_size_request(grid, 1000, -1);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 20);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 20);
    gtk_box_pack_start(GTK_BOX(lower_box), grid, FALSE, FALSE, 30);

    GtkWidget **entries = (GtkWidget **)g_malloc(11 * sizeof(GtkWidget *));

    PangoAttrList *attr_list_text = pango_attr_list_new();
    PangoAttribute *attr_size_text = pango_attr_size_new(35 * PANGO_SCALE);
    pango_attr_list_insert(attr_list_text, attr_size_text);
    PangoAttribute *attr_bold_text = pango_attr_weight_new(PANGO_WEIGHT_SEMIBOLD);
    pango_attr_list_insert(attr_list_text, attr_bold_text);

    PangoAttrList *attr_list_entry = pango_attr_list_new();
    PangoAttribute *attr_size_entry = pango_attr_size_new(25 * PANGO_SCALE);
    pango_attr_list_insert(attr_list_entry, attr_size_entry);

    GtkWidget *username_label = gtk_label_new("                       Current Password:");
    gtk_label_set_attributes(GTK_LABEL(username_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), username_label, 0, 0, 1, 1);

    entries[0] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[0]), "Enter the password");
    gtk_entry_set_attributes(GTK_ENTRY(entries[0]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[0]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[0], 1, 0, 1, 1);

    GtkWidget *password_label = gtk_label_new("                        New Password:");
    gtk_label_set_attributes(GTK_LABEL(password_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), password_label, 0, 1, 1, 1);

    entries[1] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[1]), "Enter new password");
    gtk_entry_set_attributes(GTK_ENTRY(entries[1]), attr_list_entry);
    gtk_entry_set_visibility(GTK_ENTRY(entries[1]), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(entries[1]), '*');
    gtk_grid_attach(GTK_GRID(grid), entries[1], 1, 1, 1, 1);

    GtkWidget *confirm_password_label = gtk_label_new("                    Confirm Password:");
    gtk_label_set_attributes(GTK_LABEL(confirm_password_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), confirm_password_label, 0, 2, 1, 1);

    entries[2] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[2]), "Repeat new password");
    gtk_entry_set_attributes(GTK_ENTRY(entries[2]), attr_list_entry);
    gtk_entry_set_visibility(GTK_ENTRY(entries[2]), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(entries[2]), '*');
    gtk_grid_attach(GTK_GRID(grid), entries[2], 1, 2, 1, 1);

    GtkWidget *account_type_label = gtk_label_new("                    Account Type:");
    gtk_label_set_attributes(GTK_LABEL(account_type_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), account_type_label, 0, 3, 1, 1);

    entries[3] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[3]), "Enter account type");
    gtk_entry_set_attributes(GTK_ENTRY(entries[3]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[3]), 50);
    gtk_grid_attach(GTK_GRID(grid),  entries[3], 1, 3, 1, 1);

    GtkWidget *phone_number_label = gtk_label_new("                      Phone Number:");
    gtk_label_set_attributes(GTK_LABEL(phone_number_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), phone_number_label, 0, 4, 1, 1);

    entries[4] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[4]), "Enter your phone number");
    gtk_entry_set_attributes(GTK_ENTRY(entries[4]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[4]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[4], 1, 4, 1, 1);

    GtkWidget *first_name_label = gtk_label_new("                   First Name:");
    gtk_label_set_attributes(GTK_LABEL(first_name_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), first_name_label, 2, 0, 1, 1);

    entries[5] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[5]), "Enter your first name");
    gtk_entry_set_attributes(GTK_ENTRY(entries[5]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[5]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[5], 3, 0, 1, 1);

    GtkWidget *second_name_label = gtk_label_new("                  Second Name:");
    gtk_label_set_attributes(GTK_LABEL(second_name_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), second_name_label, 2, 1, 1, 1);

    entries[6] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[6]), "Enter your second name");
    gtk_entry_set_attributes(GTK_ENTRY(entries[6]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[6]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[6], 3, 1, 1, 1);

    GtkWidget *day_birthday_label = gtk_label_new("                   Birthday Day:");
    gtk_label_set_attributes(GTK_LABEL(day_birthday_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), day_birthday_label, 2, 2, 1, 1);

    entries[7] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[7]), "Enter the day");
    gtk_entry_set_attributes(GTK_ENTRY(entries[7]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[7]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[7], 3, 2, 1, 1);

    GtkWidget *month_birthday_label = gtk_label_new("                  Birthday Month:");
    gtk_label_set_attributes(GTK_LABEL(month_birthday_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), month_birthday_label, 2, 3, 1, 1);

    entries[8] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[8]), "Enter the month");
    gtk_entry_set_attributes(GTK_ENTRY(entries[8]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[8]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[8], 3, 3, 1, 1);

    GtkWidget *year_birthday_label = gtk_label_new("                  Birthday Year:");
    gtk_label_set_attributes(GTK_LABEL(year_birthday_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), year_birthday_label, 2, 4, 1, 1);

    entries[9] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[9]), "Enter the year");
    gtk_entry_set_attributes(GTK_ENTRY(entries[9]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[9]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[9], 3, 4, 1, 1);

    GtkWidget *save_changes = gtk_button_new_with_label("Save Changes");
    GtkWidget *cancel = gtk_button_new_with_label("Cancel");

    const char *css = "label { font-size: 45px; font-weight: 600; }";
    GtkCssProvider *buttons_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(buttons_provider, css, -1, NULL);
    GtkWidget *buttons[] = {save_changes, cancel};
    for (int i = 0; i < G_N_ELEMENTS(buttons); i++) {
        GtkWidget *label = gtk_bin_get_child(GTK_BIN(buttons[i]));
        gtk_style_context_add_provider(gtk_widget_get_style_context(label), GTK_STYLE_PROVIDER(buttons_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        if (i == 0) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(edit_an_account), entries);
        } else if (i == 1) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(show_account_interface), NULL);
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(close_window), edit_account_window);
        }
        gtk_box_pack_start(GTK_BOX(lower_box), buttons[i], TRUE, TRUE, 0);
    }
    g_object_unref(buttons_provider);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_main_box), main_box);
    gtk_widget_show_all(GTK_WIDGET(edit_account_window));
    gtk_widget_destroy(data);
}

// Create new window with all account options after the user is loggeed.
void show_account_interface() {

    GtkWidget *youraccount_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_icon_from_file("images/bank_icon.png", NULL);
    gtk_window_set_title(GTK_WINDOW(youraccount_window), "GentlixBank - Application");
    gtk_window_set_default_size(GTK_WINDOW(youraccount_window), 800, 1000);
    gtk_window_maximize(GTK_WINDOW(youraccount_window));

    GtkWidget *overlay_main_box = gtk_overlay_new();
    gtk_container_add(GTK_CONTAINER(youraccount_window), overlay_main_box);
    GtkWidget *image_app_background = gtk_image_new_from_file("images/app_background.png");
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_main_box), image_app_background);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_set_spacing(GTK_BOX(main_box), 50);
    gtk_container_set_border_width(GTK_CONTAINER(main_box), 50);

    GtkWidget *upper_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_size_request(GTK_WIDGET(upper_box), -1, 320);
    gtk_box_pack_start(GTK_BOX(main_box), upper_box, TRUE, TRUE, 0);

    GtkWidget *overlay_upper_box = gtk_overlay_new();
    gtk_box_pack_start(GTK_BOX(upper_box), overlay_upper_box, TRUE, TRUE, 0);
    GtkWidget *image_background = gtk_image_new_from_file("images/main_background.jpg");
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_upper_box), image_background);

    GtkWidget *content_box_for_upper_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *image_logo = gtk_image_new_from_file("images/bank_logo.png");
    gtk_box_pack_start(GTK_BOX(content_box_for_upper_box), image_logo, FALSE, FALSE, 50);

    GtkWidget *text_title = gtk_label_new("Your account");
    const gchar *css_title_format = "label { font-size: 72px; color: #FFDFAF; font-weight: bold; }";
    GtkCssProvider *title_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(title_provider, css_title_format, -1, NULL);
    GtkStyleContext *title_context = gtk_widget_get_style_context(text_title);
    gtk_style_context_add_provider(title_context, GTK_STYLE_PROVIDER(title_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(title_provider);

    gchar *text_for_subtitle = g_strdup_printf("Welcome %s!\nAccount balance: %.2f$", account_database[current_account].first_name, account_database[current_account].account_balace);
    GtkWidget *text_subtitle = gtk_label_new(NULL);
    gtk_label_set_text(GTK_LABEL(text_subtitle), text_for_subtitle);
    const gchar *css_subtitle_format = "label { font-size: 48px; color: #E7E7E7; font-weight: 550; }";
    GtkCssProvider *subtitle_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(subtitle_provider, css_subtitle_format, -1, NULL);
    GtkStyleContext *subtitle_context = gtk_widget_get_style_context(text_subtitle);
    gtk_style_context_add_provider(subtitle_context, GTK_STYLE_PROVIDER(subtitle_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(subtitle_provider);

    gtk_box_pack_start(GTK_BOX(content_box_for_upper_box), text_title, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(content_box_for_upper_box), text_subtitle, FALSE, FALSE, 0);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_upper_box), content_box_for_upper_box);

    GtkWidget *lower_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 30);
    gtk_widget_set_size_request(GTK_WIDGET(lower_box), -1, 400);
    gtk_box_pack_start(GTK_BOX(main_box), lower_box, TRUE, TRUE, 0);

    GtkWidget *new_transaction = gtk_button_new_with_label("New transaction");
    GtkWidget *transactions_button = gtk_button_new_with_label("Your transactions");
    GtkWidget *statements_button = gtk_button_new_with_label("Account statements");
    GtkWidget *edit_button = gtk_button_new_with_label("Edit account");
    GtkWidget *delete_button = gtk_button_new_with_label("Delete account");
    GtkWidget *logout_button = gtk_button_new_with_label("Logout");

    const char *css = "label { font-size: 45px; font-weight: 600; }";
    GtkCssProvider *buttons_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(buttons_provider, css, -1, NULL);
    GtkWidget *buttons[] = {new_transaction, transactions_button, statements_button, edit_button, delete_button, logout_button};
    for (int i = 0; i < G_N_ELEMENTS(buttons); i++) {
        GtkWidget *label = gtk_bin_get_child(GTK_BIN(buttons[i]));
        gtk_style_context_add_provider(gtk_widget_get_style_context(label), GTK_STYLE_PROVIDER(buttons_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        if (i == 0) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(show_new_transaction_interface), youraccount_window);
        } else if (i == 1) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(show_all_transactions_interface), youraccount_window);
        } else if (i == 2) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(show_window), NULL);
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(close_window), NULL);
        } else if (i == 3) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(show_edit_account_interface), youraccount_window);
        } else if (i == 4) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(delete_an_account), NULL);
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(show_window), main_menu);
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(close_window), youraccount_window);
        } else if (i == 5) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(logout_from_an_account), NULL);
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(show_window), main_menu);
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(close_window), youraccount_window);
        }
        gtk_box_pack_start(GTK_BOX(lower_box), buttons[i], TRUE, TRUE, 0);
    }
    g_object_unref(buttons_provider);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_main_box), main_box);
    gtk_widget_show_all(GTK_WIDGET(youraccount_window));
}

// Create the login interface with input fields
// GtkWidget *widget - isn't used inside the function but is required from previous gtk function call
// gpointer data - provides the window from which this menu was opened to hide it
void show_login_interface(GtkWidget *widget, gpointer data) {

    GtkWidget *login_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    last_window = login_window;
    gtk_window_set_default_icon_from_file("images/bank_icon.png", NULL);
    gtk_window_set_title(GTK_WINDOW(login_window), "GentlixBank - Application");
    gtk_window_set_default_size(GTK_WINDOW(login_window), 800, 1000);
    gtk_window_maximize(GTK_WINDOW(login_window));

    GtkWidget *overlay_main_box = gtk_overlay_new();
    gtk_container_add(GTK_CONTAINER(login_window), overlay_main_box);
    GtkWidget *image_app_background = gtk_image_new_from_file("images/app_background.png");
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_main_box), image_app_background);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_set_spacing(GTK_BOX(main_box), 50);
    gtk_container_set_border_width(GTK_CONTAINER(main_box), 50);

    GtkWidget *upper_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_size_request(GTK_WIDGET(upper_box), -1, 320);
    gtk_box_pack_start(GTK_BOX(main_box), upper_box, TRUE, TRUE, 0);

    GtkWidget *overlay_upper_box = gtk_overlay_new();
    gtk_box_pack_start(GTK_BOX(upper_box), overlay_upper_box, TRUE, TRUE, 0);
    GtkWidget *image_background = gtk_image_new_from_file("images/main_background.jpg");
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_upper_box), image_background);

    GtkWidget *content_box_for_upper_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *image_logo = gtk_image_new_from_file("images/bank_logo.png");
    gtk_box_pack_start(GTK_BOX(content_box_for_upper_box), image_logo, FALSE, FALSE, 50);

    GtkWidget *text_title = gtk_label_new("Login");
    const gchar *css_title_format = "label { font-size: 72px; color: #FFDFAF; font-weight: bold; }";
    GtkCssProvider *title_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(title_provider, css_title_format, -1, NULL);
    GtkStyleContext *title_context = gtk_widget_get_style_context(text_title);
    gtk_style_context_add_provider(title_context, GTK_STYLE_PROVIDER(title_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(title_provider);

    GtkWidget *text_subtitle = gtk_label_new("Enter your account!");
    const gchar *css_subtitle_format = "label { font-size: 48px; color: #E7E7E7; font-weight: 550; }";
    GtkCssProvider *subtitle_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(subtitle_provider, css_subtitle_format, -1, NULL);
    GtkStyleContext *subtitle_context = gtk_widget_get_style_context(text_subtitle);
    gtk_style_context_add_provider(subtitle_context, GTK_STYLE_PROVIDER(subtitle_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(subtitle_provider);

    gtk_box_pack_start(GTK_BOX(content_box_for_upper_box), text_title, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(content_box_for_upper_box), text_subtitle, FALSE, FALSE, 0);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_upper_box), content_box_for_upper_box);

    GtkWidget *lower_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 30);
    gtk_widget_set_size_request(GTK_WIDGET(lower_box), -1, 400);
    gtk_box_pack_start(GTK_BOX(main_box), lower_box, TRUE, TRUE, 0);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_size_request(grid, 100, -1);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 20);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 20);
    gtk_box_pack_start(GTK_BOX(lower_box), grid, FALSE, FALSE, 30);

    GtkWidget **entries = (GtkWidget **)g_malloc(3 * sizeof(GtkWidget *)); // Dynamic allocation for inputs

    // Create a list of formats for the text in front of input field
    PangoAttrList *attr_list_text = pango_attr_list_new();
    PangoAttribute *attr_size_text = pango_attr_size_new(35 * PANGO_SCALE);
    pango_attr_list_insert(attr_list_text, attr_size_text);
    PangoAttribute *attr_bold_text = pango_attr_weight_new(PANGO_WEIGHT_SEMIBOLD);
    pango_attr_list_insert(attr_list_text, attr_bold_text);

    // Create a list of formats for the text from input field
    PangoAttrList *attr_list_entry = pango_attr_list_new();
    PangoAttribute *attr_size_entry = pango_attr_size_new(25 * PANGO_SCALE);
    pango_attr_list_insert(attr_list_entry, attr_size_entry);

    GtkWidget *username_label = gtk_label_new("                            Usertag:");
    gtk_label_set_attributes(GTK_LABEL(username_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), username_label, 0, 0, 1, 1);

    entries[0] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[0]), "Enter your account tag");
    gtk_entry_set_attributes(GTK_ENTRY(entries[0]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[0]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[0], 1, 0, 1, 1);

    GtkWidget *password_label = gtk_label_new("                          Password:");
    gtk_label_set_attributes(GTK_LABEL(password_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), password_label, 2, 0, 1, 1);

    entries[1] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[1]), "Enter account password");
    gtk_entry_set_attributes(GTK_ENTRY(entries[1]), attr_list_entry);
    gtk_entry_set_visibility(GTK_ENTRY(entries[1]), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(entries[1]), '*');
    gtk_entry_set_width_chars(GTK_ENTRY(entries[1]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[1], 3, 0, 1, 1);

    GtkWidget *blanck_label = gtk_label_new(" \n");
    gtk_label_set_attributes(GTK_LABEL(blanck_label), attr_list_text);

    GtkWidget *blanck_label2 = gtk_label_new(" \n");
    gtk_label_set_attributes(GTK_LABEL(blanck_label), attr_list_text);

    GtkWidget *blanck_label3 = gtk_label_new(" \n");
    gtk_label_set_attributes(GTK_LABEL(blanck_label), attr_list_text);

    gtk_grid_attach(GTK_GRID(grid), blanck_label, 0, 2, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), blanck_label2, 0, 3, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), blanck_label3, 0, 4, 2, 1);

    GtkWidget *login_button = gtk_button_new_with_label("Login");
    GtkWidget *close_button = gtk_button_new_with_label("Close");

    const char *css = "label { font-size: 45px; font-weight: 600; }";
    GtkCssProvider *buttons_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(buttons_provider, css, -1, NULL);
    GtkWidget *buttons[] = {login_button, close_button};
    for (int i = 0; i < G_N_ELEMENTS(buttons); i++) {
        GtkWidget *label = gtk_bin_get_child(GTK_BIN(buttons[i]));
        gtk_style_context_add_provider(gtk_widget_get_style_context(label), GTK_STYLE_PROVIDER(buttons_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        if (i == 0) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(login_to_an_account), entries);
        } else if (i == 1) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(show_window), data);
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(close_window), login_window);
        }
        gtk_box_pack_start(GTK_BOX(lower_box), buttons[i], TRUE, TRUE, 0);
    }
    g_object_unref(buttons_provider);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_main_box), main_box);
    gtk_widget_show_all(GTK_WIDGET(login_window));
    gtk_widget_hide(data);  // Hide main menu to be able to show it anytime
}

// Create the register interface with input fields.
// GtkWidget *widget - isn't used inside the function but is required from previous gtk function call
// gpointer data - provides the window from which this menu was opened to hide it
void show_register_interface(GtkWidget *widget, gpointer data) {

    GtkWidget *register_window = gtk_window_new(GTK_WINDOW_TOPLEVEL); // Create a new window for register interface
    last_window = register_window; // The window is saved in a global variable to be able from any to destory it
    gtk_window_set_default_icon_from_file("images/bank_icon.png", NULL);
    gtk_window_set_title(GTK_WINDOW(register_window), "GentlixBank - Application");
    gtk_window_set_default_size(GTK_WINDOW(register_window), 800, 1000);
    gtk_window_maximize(GTK_WINDOW(register_window));

    GtkWidget *overlay_main_box = gtk_overlay_new();
    gtk_container_add(GTK_CONTAINER(register_window), overlay_main_box);
    GtkWidget *image_app_background = gtk_image_new_from_file("images/app_background.png");
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_main_box), image_app_background);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_set_spacing(GTK_BOX(main_box), 50);
    gtk_container_set_border_width(GTK_CONTAINER(main_box), 50);

    GtkWidget *upper_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_size_request(GTK_WIDGET(upper_box), -1, 320);
    gtk_box_pack_start(GTK_BOX(main_box), upper_box, TRUE, TRUE, 0);

    GtkWidget *overlay_upper_box = gtk_overlay_new();
    gtk_box_pack_start(GTK_BOX(upper_box), overlay_upper_box, TRUE, TRUE, 0);
    GtkWidget *image_background = gtk_image_new_from_file("images/main_background.jpg");
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_upper_box), image_background);

    GtkWidget *content_box_for_upper_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *image_logo = gtk_image_new_from_file("images/bank_logo.png");
    gtk_box_pack_start(GTK_BOX(content_box_for_upper_box), image_logo, FALSE, FALSE, 50);

    GtkWidget *text_title = gtk_label_new("Register");
    const gchar *css_title_format = "label { font-size: 72px; color: #FFDFAF; font-weight: bold; }";
    GtkCssProvider *title_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(title_provider, css_title_format, -1, NULL);
    GtkStyleContext *title_context = gtk_widget_get_style_context(text_title);
    gtk_style_context_add_provider(title_context, GTK_STYLE_PROVIDER(title_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(title_provider);

    GtkWidget *text_subtitle = gtk_label_new("Create a new account!");
    const gchar *css_subtitle_format = "label { font-size: 48px; color: #E7E7E7; font-weight: 550; }";
    GtkCssProvider *subtitle_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(subtitle_provider, css_subtitle_format, -1, NULL);
    GtkStyleContext *subtitle_context = gtk_widget_get_style_context(text_subtitle);
    gtk_style_context_add_provider(subtitle_context, GTK_STYLE_PROVIDER(subtitle_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(subtitle_provider);

    gtk_box_pack_start(GTK_BOX(content_box_for_upper_box), text_title, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(content_box_for_upper_box), text_subtitle, FALSE, FALSE, 0);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_upper_box), content_box_for_upper_box);

    GtkWidget *lower_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 30);
    gtk_widget_set_size_request(GTK_WIDGET(lower_box), -1, 400);
    gtk_box_pack_start(GTK_BOX(main_box), lower_box, TRUE, TRUE, 0);

    GtkWidget *grid = gtk_grid_new(); // Used to make a table with input fields
    gtk_widget_set_size_request(grid, 1000, -1);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 20);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 20);
    gtk_box_pack_start(GTK_BOX(lower_box), grid, FALSE, FALSE, 30);

    GtkWidget **entries = (GtkWidget **)g_malloc(11 * sizeof(GtkWidget *)); // Dynamic allocation for inputs

    // Create a list of formats for the text in front of input field
    PangoAttrList *attr_list_text = pango_attr_list_new();
    PangoAttribute *attr_size_text = pango_attr_size_new(35 * PANGO_SCALE);
    pango_attr_list_insert(attr_list_text, attr_size_text);
    PangoAttribute *attr_bold_text = pango_attr_weight_new(PANGO_WEIGHT_SEMIBOLD);
    pango_attr_list_insert(attr_list_text, attr_bold_text);

    // Create a list of formats for the text from input field
    PangoAttrList *attr_list_entry = pango_attr_list_new();
    PangoAttribute *attr_size_entry = pango_attr_size_new(25 * PANGO_SCALE);
    pango_attr_list_insert(attr_list_entry, attr_size_entry);

    // Because gtk don't have a feature which can center the grid inside the box
    // on windows 11 I used spaces for that
    GtkWidget *username_label = gtk_label_new("                        Usertag:");
    gtk_label_set_attributes(GTK_LABEL(username_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), username_label, 0, 0, 1, 1);

    entries[0] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[0]), "Enter an account tag");
    gtk_entry_set_attributes(GTK_ENTRY(entries[0]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[0]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[0], 1, 0, 1, 1);

    GtkWidget *password_label = gtk_label_new("                        Password:");
    gtk_label_set_attributes(GTK_LABEL(password_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), password_label, 0, 1, 1, 1);

    entries[1] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[1]), "Enter account password");
    gtk_entry_set_attributes(GTK_ENTRY(entries[1]), attr_list_entry);
    gtk_entry_set_visibility(GTK_ENTRY(entries[1]), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(entries[1]), '*');
    gtk_grid_attach(GTK_GRID(grid), entries[1], 1, 1, 1, 1);

    GtkWidget *confirm_password_label = gtk_label_new("                    Confirm Password:");
    gtk_label_set_attributes(GTK_LABEL(confirm_password_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), confirm_password_label, 0, 2, 1, 1);

    entries[2] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[2]), "Repeat account password");
    gtk_entry_set_attributes(GTK_ENTRY(entries[2]), attr_list_entry);
    gtk_entry_set_visibility(GTK_ENTRY(entries[2]), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(entries[2]), '*');
    gtk_grid_attach(GTK_GRID(grid), entries[2], 1, 2, 1, 1);

    GtkWidget *account_type_label = gtk_label_new("                    Account Type:");
    gtk_label_set_attributes(GTK_LABEL(account_type_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), account_type_label, 0, 3, 1, 1);

    entries[3] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[3]), "Enter account type");
    gtk_entry_set_attributes(GTK_ENTRY(entries[3]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[3]), 50);
    gtk_grid_attach(GTK_GRID(grid),  entries[3], 1, 3, 1, 1);

    GtkWidget *phone_number_label = gtk_label_new("                      Phone Number:");
    gtk_label_set_attributes(GTK_LABEL(phone_number_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), phone_number_label, 0, 4, 1, 1);

    entries[4] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[4]), "Enter your phone number");
    gtk_entry_set_attributes(GTK_ENTRY(entries[4]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[4]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[4], 1, 4, 1, 1);

    GtkWidget *first_name_label = gtk_label_new("                   First Name:");
    gtk_label_set_attributes(GTK_LABEL(first_name_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), first_name_label, 2, 0, 1, 1);

    entries[5] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[5]), "Enter your first name");
    gtk_entry_set_attributes(GTK_ENTRY(entries[5]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[5]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[5], 3, 0, 1, 1);

    GtkWidget *second_name_label = gtk_label_new("                  Second Name:");
    gtk_label_set_attributes(GTK_LABEL(second_name_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), second_name_label, 2, 1, 1, 1);

    entries[6] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[6]), "Enter your second name");
    gtk_entry_set_attributes(GTK_ENTRY(entries[6]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[6]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[6], 3, 1, 1, 1);

    GtkWidget *day_birthday_label = gtk_label_new("                   Birthday Day:");
    gtk_label_set_attributes(GTK_LABEL(day_birthday_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), day_birthday_label, 2, 2, 1, 1);

    entries[7] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[7]), "Enter the day");
    gtk_entry_set_attributes(GTK_ENTRY(entries[7]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[7]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[7], 3, 2, 1, 1);

    GtkWidget *month_birthday_label = gtk_label_new("                  Birthday Month:");
    gtk_label_set_attributes(GTK_LABEL(month_birthday_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), month_birthday_label, 2, 3, 1, 1);

    entries[8] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[8]), "Enter the month");
    gtk_entry_set_attributes(GTK_ENTRY(entries[8]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[8]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[8], 3, 3, 1, 1);

    GtkWidget *year_birthday_label = gtk_label_new("                  Birthday Year:");
    gtk_label_set_attributes(GTK_LABEL(year_birthday_label), attr_list_text);
    gtk_grid_attach(GTK_GRID(grid), year_birthday_label, 2, 4, 1, 1);

    entries[9] = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entries[9]), "Enter the year");
    gtk_entry_set_attributes(GTK_ENTRY(entries[9]), attr_list_entry);
    gtk_entry_set_width_chars(GTK_ENTRY(entries[9]), 50);
    gtk_grid_attach(GTK_GRID(grid), entries[9], 3, 4, 1, 1);

    GtkWidget *create_account_button = gtk_button_new_with_label("Create account");
    GtkWidget *close_button = gtk_button_new_with_label("Close");

    const char *css = "label { font-size: 45px; font-weight: 600; }";
    GtkCssProvider *buttons_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(buttons_provider, css, -1, NULL);
    GtkWidget *buttons[] = {create_account_button, close_button};
    for (int i = 0; i < G_N_ELEMENTS(buttons); i++) {
        GtkWidget *label = gtk_bin_get_child(GTK_BIN(buttons[i]));
        gtk_style_context_add_provider(gtk_widget_get_style_context(label), GTK_STYLE_PROVIDER(buttons_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        if (i == 0) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(create_an_account), entries);
        } else if (i == 1) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(show_window), data);
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(close_window), register_window);
        }
        gtk_box_pack_start(GTK_BOX(lower_box), buttons[i], TRUE, TRUE, 0);
    }
    g_object_unref(buttons_provider);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_main_box), main_box);
    gtk_widget_show_all(GTK_WIDGET(register_window));
    gtk_widget_hide(data); // Hide main menu to be able to show it anytime
}

void show_import_interface(GtkWidget *widget, gpointer data) {
}

void show_export_interface(GtkWidget *widget, gpointer data) {
}

// Create main window and it's widgets. Here are the first options when you open the app.
// GtkApplication *app - provides a reference to the GTK application object, which you can use to interact with the
// GTK application and perform various operations through it. Here is used only to create the main window for the linked app for int main.
// gpointer data - is a generic pointer that can be used to pass additional data to the callback function. Here is passed a NULL one.
void activate_main_menu(GtkApplication *app, gpointer data) {

    // More about app layout and format inside the documentation file
    GtkWidget * main_window = gtk_application_window_new(app); // The main_window with main menu for app
    main_menu = main_window;  // The main main_window is saved in a global variable to be able from any function to show or hide it
    gtk_window_set_default_icon_from_file("images/bank_icon.png", NULL);
    gtk_window_set_title(GTK_WINDOW(main_window), "GentlixBank - Application");
    gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 1000);
    gtk_window_maximize(GTK_WINDOW(main_window));

    GtkWidget *overlay_main_box = gtk_overlay_new();
    gtk_container_add(GTK_CONTAINER(main_window), overlay_main_box);
    GtkWidget *image_app_background = gtk_image_new_from_file("images/app_background.png");
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_main_box), image_app_background);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_set_spacing(GTK_BOX(main_box), 50);
    gtk_container_set_border_width(GTK_CONTAINER(main_box), 50);

    GtkWidget *upper_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_size_request(GTK_WIDGET(upper_box), -1, 320);
    gtk_box_pack_start(GTK_BOX(main_box), upper_box, TRUE, TRUE, 0);

    GtkWidget *overlay_upper_box = gtk_overlay_new();
    gtk_box_pack_start(GTK_BOX(upper_box), overlay_upper_box, TRUE, TRUE, 0);
    GtkWidget *image_background = gtk_image_new_from_file("images/main_background.jpg");
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_upper_box), image_background);

    GtkWidget *content_box_for_upper_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *image_logo = gtk_image_new_from_file("images/bank_logo.png");
    gtk_box_pack_start(GTK_BOX(content_box_for_upper_box), image_logo, FALSE, FALSE, 50);

    GtkWidget *text_title = gtk_label_new("Gentlix Bank");
    const gchar *css_title_format = "label { font-size: 72px; color: #FFDFAF; font-weight: bold; }";
    GtkCssProvider *title_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(title_provider, css_title_format, -1, NULL);
    GtkStyleContext *title_context = gtk_widget_get_style_context(text_title);
    gtk_style_context_add_provider(title_context, GTK_STYLE_PROVIDER(title_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(title_provider);

    GtkWidget *text_subtitle = gtk_label_new("Welcome back!");
    const gchar *css_subtitle_format = "label { font-size: 48px; color: #E7E7E7; font-weight: 550; }";
    GtkCssProvider *subtitle_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(subtitle_provider, css_subtitle_format, -1, NULL);
    GtkStyleContext *subtitle_context = gtk_widget_get_style_context(text_subtitle);
    gtk_style_context_add_provider(subtitle_context, GTK_STYLE_PROVIDER(subtitle_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(subtitle_provider);

    gtk_box_pack_start(GTK_BOX(content_box_for_upper_box), text_title, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(content_box_for_upper_box), text_subtitle, FALSE, FALSE, 0);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_upper_box), content_box_for_upper_box);

    GtkWidget *lower_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 30);
    gtk_widget_set_size_request(GTK_WIDGET(lower_box), -1, 400);
    gtk_box_pack_start(GTK_BOX(main_box), lower_box, TRUE, TRUE, 0);

    GtkWidget *login_button = gtk_button_new_with_label("Login");
    GtkWidget *register_button = gtk_button_new_with_label("Register");
    GtkWidget *admin_button = gtk_button_new_with_label("Admin");
    GtkWidget *close_button = gtk_button_new_with_label("Close");

    const char *css = "label { font-size: 45px; font-weight: 600; }";
    GtkCssProvider *buttons_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(buttons_provider, css, -1, NULL);
    GtkWidget *buttons[] = {login_button, register_button, admin_button, close_button};
    for (int i = 0; i < G_N_ELEMENTS(buttons); i++) {
        GtkWidget *label = gtk_bin_get_child(GTK_BIN(buttons[i]));
        gtk_style_context_add_provider(gtk_widget_get_style_context(label), GTK_STYLE_PROVIDER(buttons_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        if (i == 0) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(show_login_interface), main_window);
        } else if (i == 1) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(show_register_interface), main_window);
        } else if (i == 2) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(show_import_interface), NULL);
        } else if (i == 3) {
            g_signal_connect(G_OBJECT(buttons[i]), "clicked", G_CALLBACK(close_window), G_OBJECT(main_window));
        }
        gtk_box_pack_start(GTK_BOX(lower_box), buttons[i], TRUE, TRUE, 0);
    }
    g_object_unref(buttons_provider);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay_main_box), main_box);
    gtk_widget_show_all(main_window); // Show the main_window after all formats
}

// Create the GTK Application, activate the main window for it and return the run status.
// int arc - represents the number of command-line arguments passed to the program and is required for GTK Library
// char *argv[] - representing the command-line arguments. Each element of the array is a string containing one of the command-line arguments.
// Return application_status after activate.
int main(int argc, char *argv[]) {

    GtkApplication * main_application;
    int application_status; // If run fail will return the error code.

    main_application = gtk_application_new("com.bank.GentlixBank", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(main_application, "activate", G_CALLBACK(activate_main_menu), NULL); // Create and show the main window
    application_status = g_application_run(G_APPLICATION(main_application), argc, argv);
    g_object_unref(main_application);

    return application_status;
}
