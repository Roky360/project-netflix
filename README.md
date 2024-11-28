# project-netflix

_Avi Ben David, Kfir Eitan, Eden Shaked_

Advanced Programming project - Netflix App.

## Important Links

- [GitHub (This repo)](https://github.com/Roky360/project-netflix)
- [Jira](https://edenshkd.atlassian.net/jira/software/projects/NP/boards/2/backlog)

---

## How to Run

### Run with Docker

To run the app with Docker, you need to have **Docker Desktop** installed, and to **clone** the repo with:

```
git clone https://github.com/Roky360/project-netflix.git
```

> #### To build and run the app, run:
>
> ```bash
> docker-compose up app
> ```
>
> Then to use the terminal to interact with the app, run (you may need to open another terminal):
>
> ```bash
> docker attach project-netflix-app-1
> ```
>
> Finally, to stop the app, run:
>
> ```bash
> docker stop project-netflix-app-1
> ```
>

> #### To run the unit-tests, run:
> ```bash
> docker-compose up test
> ```

## Available Commands

Right now, the server supports these commands:

* ### Add

  Marks movie(s) as watched by a certain user.

  > **add** user-id [movie-id-1] [movie-id-2] ...

  #### Example: `add 1 101 102 103 110`

* ### Recommend

  Recommends to a user up to 10 movies similar to a given movie, based on other users' taste.

  > **recommend** [user-id] [movie-id]

  #### Example: `recommend 1 108`

* ### Help

  Displays all the available commands.

  > **help**






