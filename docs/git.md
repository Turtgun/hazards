# Explanation of git

## Commands

These are the things you put in your terminal

### git init

Initializes a brand new Git repository and begins tracking an existing directory. It adds a hidden subfolder within the existing directory that houses the internal data structure required for version control.

### git clone

Creates a local copy of a project that already exists remotely. The clone includes all the project's files, history, and branches.

### git add

Stages a change. Git tracks changes to a developer's codebase, but it's necessary to stage and take a snapshot of the changes to include them in the project's history. This command performs staging, the first part of that two-step process. Any changes that are staged will become a part of the next snapshot and a part of the project's history. Staging and committing separately gives developers complete control over the history of their project without changing how they code and work.

### git commit

Saves the snapshot to the project history and completes the change-tracking process. In short, a commit functions like taking a photo. Anything that's been staged with git add will become a part of the snapshot with git commit.

### git status

Shows the status of changes as untracked, modified, or staged.

### git branch

Shows the branches being worked on locally.

### git merge

Merges lines of development together. This command is typically used to combine changes made on two distinct branches. For example, a developer would merge when they want to combine changes from a feature branch into the main branch for deployment.

### git pull

Updates the local line of development with updates from its remote counterpart. Developers use this command if a teammate has made commits to a branch on a remote, and they would like to reflect those changes in their local environment.

### git push

Updates the remote repository with any commits made locally to a branch.

## git for VSCode

If running these things in terminal is something you find difficult or just time consuming you can use the built in VSCode

Just use [this link](https://code.visualstudio.com/docs/sourcecontrol/overview) to get a good understanding on how to use git in VSCode.
