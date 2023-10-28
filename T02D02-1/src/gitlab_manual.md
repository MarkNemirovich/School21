# Creating a personal repository with the correct .gitignore and simple README
## Creating a repo
To put your project up on Git, you'll need to create a repository for it to live in. Almost all git services support function of adding new repository.

## Adding gitignore file
Git sees every file in your working copy as one of three things:
- tracked - a file which has been previously staged or committed;
- untracked - a file which has not been staged or committed; or
- ignored - a file which Git has been explicitly told to ignore.

Ignored files are usually build artifacts and machine generated files that can be derived from your repository source or should otherwise not be committed.

### README files
A README file is a text file  containing information for the user about the software program or utility. README files often contain instructions and additional help, and details about patches or updates.
Flag button will help you to create README file when you create a new repository or project:

![](https://www.google.com/url?sa=i&url=https%3A%2F%2Fbiogitflow.readthedocs.io%2Fen%2Flatest%2Fgitlab.html&psig=AOvVaw2VR9Nbtg2wnPX5EbNnDFBo&ust=1698308082694000&source=images&cd=vfe&opi=89978449&ved=0CBEQjRxqFwoTCMjSxuHgkIIDFQAAAAAdAAAAABAI)


# Creating develop and master branches
To create new branch we use command "git chechout -b <branchname>"
Main branch in repo often called "master" and the branch in which we will work is "develop"
Branches are pointers to the version of the program:

![](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.decodingdevops.com%2Fhow-to-create-a-branch-in-gitlab-create-a-new-branch%2F&psig=AOvVaw1UP9h6yNTRsbXh9tFtolyR&ust=1698308583452000&source=images&cd=vfe&opi=89978449&ved=0CBEQjRxqFwoTCNjLsNDikIIDFQAAAAAdAAAAABAJ)

# Setting the develop branch as the default
To choose branch we use command "git checkout <branchname>" if it already exists
To choose develop branch we type "git checkout develop" and start working. And we start working in it as in the main

![](https://www.google.com/url?sa=i&url=https%3A%2F%2Fstackoverflow.com%2Fquestions%2F30987216%2Fchange-default-branch-in-gitlab&psig=AOvVaw3lhi82qBpJBuT9nGkhIBId&ust=1698308662503000&source=images&cd=vfe&opi=89978449&ved=0CBEQjRxqFwoTCKDKivbikIIDFQAAAAAdAAAAABAE)

# Creating an issue for creating the current manual
Use issues to collaborate on ideas, solve problems, and plan work. Share and discuss proposals with your team and with outside collaborators.
You can use issues for many purposes, customized to your needs and workflow.

- Discuss the implementation of an idea.
- Track tasks and work status.
- Accept feature proposals, questions, support requests, or bug reports.
- Elaborate on code implementations.

To make an issue on gitlab you need to navigate to Projects Dashboard > Issues > New issue

![](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.tutorialspoint.com%2Fgitlab%2Fgitlab_create_issue.htm&psig=AOvVaw29NtPEBIo3st5SLRc0mNch&ust=1698308721218000&source=images&cd=vfe&opi=89978449&ved=0CBEQjRxqFwoTCMDPkpLjkIIDFQAAAAAdAAAAABAE)

![](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.tutorialspoint.com%2Fgitlab%2Fgitlab_create_issue.htm&psig=AOvVaw29NtPEBIo3st5SLRc0mNch&ust=1698308721218000&source=images&cd=vfe&opi=89978449&ved=0CBEQjRxqFwoTCMDPkpLjkIIDFQAAAAAdAAAAABAJ)

# Creating a branch for the issue
To solve the problem we may create the new branch (to avoid damaging a working part of the programm) by using "git chechout -b <issue fix>"

![](https://www.google.com/url?sa=i&url=https%3A%2F%2Fgitlab.com%2Fgitlab-org%2Fgitlab%2F-%2Fissues%2F20577&psig=AOvVaw1Cs47dxl3_yltFpKgK9wpX&ust=1698308794782000&source=images&cd=vfe&opi=89978449&ved=0CBEQjRxqFwoTCNDikLXjkIIDFQAAAAAdAAAAABAX)

# Creating a merge request on the develop branch
If your development workflow requires an issue for every merge request, you can create a branch directly from the issue to speed the process up. The new branch, and later its merge request, are marked as related to this issue. Once merged, the merge request closes the issue. 

![](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.tutorialspoint.com%2Fgitlab%2Fgitlab_merge_requests.htm&psig=AOvVaw0NxTuAggVFHGdsKT8ZETOL&ust=1698308878778000&source=images&cd=vfe&opi=89978449&ved=0CBEQjRxqFwoTCNiMld3jkIIDFQAAAAAdAAAAABBg)

![](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.tutorialspoint.com%2Fgitlab%2Fgitlab_merge_requests.htm&psig=AOvVaw0NxTuAggVFHGdsKT8ZETOL&ust=1698308878778000&source=images&cd=vfe&opi=89978449&ved=0CBEQjRxqFwoTCNiMld3jkIIDFQAAAAAdAAAAABBo)

# Commenting and accepting the request
With merge request approval rules, you can set the minimum number of required approvals before work can merge into your project. You can also extend these rules to define what types of users can approve work. Some examples of rules you can create include:

- Users with specific permissions can always approve work.
- Code owners can approve work for files they own.
- Users with specific permissions can approve work, even if they don’t have merge rights to the - - repository.
- Users with specific permissions can be allowed or denied the ability to override approval rules on a specific merge request.

![](https://www.google.com/url?sa=i&url=https%3A%2F%2Fabout.gitlab.com%2Fblog%2F2015%2F07%2F29%2Ffeature-highlight-merge-request-approvals%2F&psig=AOvVaw2Faf6STBUmwYdUDI6Q_qZe&ust=1698308966790000&source=images&cd=vfe&opi=89978449&ved=0CBEQjRxqFwoTCOjCnIfkkIIDFQAAAAAdAAAAABAI)

# Creating a stable version in the master with a tag
Like most VCSs, Git has the ability to tag specific points in a repository’s history as being important. Typically, people use this functionality to mark release points (v1.0, v2.0 and so on).  

![](https://www.google.com/url?sa=i&url=https%3A%2F%2Fstackoverflow.com%2Fquestions%2F29520905%2Fhow-to-create-releases-in-gitlab&psig=AOvVaw2PDIGe1y41DGLKmSReGzug&ust=1698309013888000&source=images&cd=vfe&opi=89978449&ved=0CBEQjRxqFwoTCJCS1Z3kkIIDFQAAAAAdAAAAABAE)

# Working with wiki for the project
If you don’t want to keep your documentation in your repository, but you want to keep it in the same project as your code, you can use the wiki GitLab provides in each GitLab project. Every wiki is a separate Git repository, so you can create wiki pages in the web interface, or locally using Git.

To access the wiki for a project or group, go to the page for your project or group and, in the left sidebar, select Wiki. If Wiki is not listed in the left sidebar, a project administrator has disabled it.

GitLab wikis support Markdown, RDoc, AsciiDoc, and Org for content. Wiki pages written in Markdown support all Markdown features, and also provide some wiki-specific behavior for links.

