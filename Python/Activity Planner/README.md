# 💻 Assignment 08 - Layered Architecture I
## Requirements
- Provide a menu-driven console-based user interface. Implementation details are up to you
- Employ layered architecture and classes
- Have at least 20 procedurally generated items **for each domain class** in your application at startup (e.g., at least 20 students, 20 disciplines and 20 grades)
- Provide specifications and **[PyUnit test cases](https://realpython.com/python-testing/)** for all non-UI classes and methods for the first functionality
- Implement and use your own exception classes.
- Deadline for maximum grade is **week 11**.

## Problem Statements

### 5. Activity Planner
The following information is stored in a personal activity planner:
- **Person**: `person_id`, `name`, `phone_number`
- **Activity**: `activity_id`, `person_id` - list, `date`, `time`, `description`

Create an application to:
1. Manage persons and activities. The user can add, remove, update, and list both persons and activities.
2. Add/remove activities. Each activity can be performed together with one or several other persons, who are already in the user’s planner. Activities must not overlap (user cannot have more than one activity at a given time).
3. Search for persons or activities. Persons can be searched for using name or phone number. Activities can be searched for using date/time or description. The search must work using case-insensitive, partial string matching, and must return all matching items.
4. Create statistics:
    - Activities for a given date. List the activities for a given date, in the order of their start time.
    - Busiest days. This will provide the list of upcoming dates with activities, sorted in ascending order of the free time in that day (all intervals with no activities).
    - Activities with a given person. List all upcoming activities to which a given person will participate.
