
# Git Help 
--------------------------


This file contains some of the commonly used git commands and their description. The official documentation can be found in the [Documentation](https://git-scm.com/documentation) page.

## Fetching Changes From Upstream
The changes from the upstream can be downloaded using `git fetch upstream`.

## Switching branches
Switching between branches can be done using `get checkout <branch_name>`.
For example:
``` 
git checkout developer
```
Simulatenously creating a new branch and switching to that new branch can be done using the `get checkout -b <branch_name>`.
For example:
``` 
git checkout -b newbranch
```

## Merging the changes from upstream to the developer branch
The changes in the upstream can be associated with the local developer branch by using the command 
`git merge upstream/developer.`

## Viewing the list of remotes
The list of remotes can be viewed using the command 
`git remote` . It lists the shortnames of each remote servers.

Using `git remote -v` shows you the URLs that Git has stored for the shortname to be used while reading and writing to that remote.

## Adding a remote 
To add a new remote , we should use the `git remote add` command on the terminal in the directory that your repository is stored at.
This command takes two arguments :
> A remote name, for example, `upstream`
> A remote URL, for example, `https://github.com/user/repo.git`

Example: Adding a new remote named upstream for a given <url>
```git remote add upstream <url>```


## Pushing commits to a remote repository 

`git push` is used to push commits made on your local branch to a remote repository. 
For example: Pushing to origin from the remote developer branch can be done using 
```git push origin developer```



