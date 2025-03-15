# Assignment
## Requirements
- You will be given one of the problems below to solve.
- The application must be implemented in C++ and use layered architecture.
- Provide tests and specifications for non-trivial functions outside the UI. Test coverage must be at least 98% for all layers, except the UI.
- Have at least 10 entities in your memory repository.
- Validate the input data.
- Handle the following situations:
    - If an entity that already exists is added, a message is shown and the entity is not stored. You must decide what makes an entity unique.
    - If the user tries to update/delete an entity that does not exist, a message will be shown and there will be no effect on the list of entities.

## Week 5
- Solve the requirements related to the administrator mode.
- Define the `DynamicVector` class which provides the specific operations: `add`, `remove`, `length`, etc. The array of elements must be dynamically allocated.

## Week 7
- Solve all problem requirements.
- `DynamicVector` must be a class template.

## Problem Statements

### Keep calm and adopt a pet
The *“Keep calm and adopt a pet”* shelter needs a software application to help them find adoptive parents for the dogs  they are taking care of. The application can be used in two modes: `administrator` and `user`. When the application is started, it will offer the option to select the mode.\
**Administrator mode:** The application will have a database that holds all the dogs in the shelter at a given moment. The shelter employees must be able to update the database, meaning: add a new dog, delete a dog (when the dog is adopted) and update the information of a dog. Each **Dog** has a `breed`, a `name`, an `age` and a `photograph`. The photograph is memorised as a link towards an online resource (the photograph on the presentation site of the centre). The administrators will also have the option to see all the dogs in the shelter.\
**User mode:** A user can access the application and choose one or more dogs to adopt. The application will allow the user to:
- See the dogs in the database, one by one. When the user chooses this option, the data of the first dog (breed, name, age) is displayed, along with its photograph.
- Choose to adopt the dog, in which case the dog is added to the user’s adoption list.
- Choose not to adopt the dog and to continue to the next. In this case, the information corresponding to the next dog is shown and the user is again offered the possibility to adopt it. This can continue as long as the user wants, as when arriving to the end of the list, if the user chooses next, the application will again show the first dog.
- See all the dogs of a given breed, having an age less than a given number. If no breed is provided, then all the dogs will be considered. The functionalities outlined above apply again in this case.
- See the adoption list.

## Week 8
- Implement at least requirements **1** and **2**.

## Week 10
- Implement all requirements
- Requirements **4** and **5** must be implemented using inheritance and polymorphism.

## Problem Statement 
For your solution to the previous assignment (Assignment 05-06), add the following features:
1. Replace the templated DynamicVector with the STL vector. Use STL algorithms wherever possible in your application (e.g. in your filter function you could use `copy_if`, `count_if`). Replace all your for loops either with STL algorithms, or with C++11's range-based for loop.

2. Store repository data in a text file. When the program starts, entities are read from the file. Modifications made during program execution are stored in the file. Implement this using the `iostream` library. Create insertion and extraction operators for your entities and use these when reading/writing to files or the console.

3. Use exceptions to signal errors:
    - from the repository;
    - validation errors – validate your entities using Validator classes;
    - create your own exception classes.
    - validate program input.

4.	Depending on your assignment, store your (adoption list, movie watch list, shopping basket or tutorial watch list) in a file. When the application starts, the user should choose the type of file between `CSV` or `HTML`. Depending on the type, the application will save the list in the correct format.

    **Indications**\
    The CSV file will contain each entity on one line and the attributes will be separated by comma \
    The HTML file will contain a table, in which each row holds the data of one entity. The columns of the table will contain the names of the data attributes.\
    These are exemplified in the [example.csv](example.csv) and [example.html](example.html) files.
    `CSV` and `HTML` files are used to save and display data to the user; they act as program outputs, so data should not be read from them!

5. Add a new command, allowing the user to see the:
    * adoption list
Displaying the list means opening the saved file (`CSV` or `HTML`) with the correct application (`CSV` files using Notepad, Notepad++, Microsoft Excel etc. and `HTML` files using a browser)

6. Create a UML class diagram for your entire application.