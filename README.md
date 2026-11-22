# Tasklog

## Commands
tasklog add task1, task2, ...
tasklog view
tasklog view today
tasklog complete ID / tasklog remove ID
tasklog details ID [TEXT]
tasklog date ID (tdy, tmrw, or MM/DD)

## Database Structure
Each table is a separate list of tasks

task
+ id, INTEGER PRIMARY KEY
+ name, TEXT (not null)
+ details, TEXT (can be null)
+ date, TEXT (can be null). eg: "1115" for Nov 15, or "0102" for Jan 2nd

## Remember to do this
Change app to use dynamic memory allocation