# Contributing

## Intro
  
This plugin enables developers to leverage LibTorch's machine-learning capabilities directly within Unreal Engine, without the need for Python. 

This project endeavours to bridge the gap between advanced machine learning techniques and the game development process, specifically within the Unreal Engine ecosystem.
Our goal is to make advanced machine-learning capabilities accessible directly within Unreal Engine through C++ and Blueprints, eliminating the need for Python integration.

We need volunteers to help this project come to fruition. So, I'm thrilled that you're taking the time to read this. 
Every contribution is valuable and helps us achieve our mission.

Here are some important resources:

  * [Setup and Basic Usage](https://youtu.be/dvGWUh4SPBY) 
  * [Working with Meta's Llama](https://youtu.be/0YI2O5uSuFw)
  * [Text-based setup guide](https://github.com/gpt-3d/pytorch/wiki)


## How to Contribute

1. **Fork and Clone:** Start by [forking the repo](https://github.com/P1ayer-1/Libtorch-UE5/fork) and [cloning your fork locally](https://docs.github.com/en/github/creating-cloning-and-archiving-repositories/cloning-a-repository).
2. **Find an Issue:** Look for [open issues](https://github.com/P1ayer-1/Libtorch-UE5/issues?q=is%3Aissue+is%3Aopen) that interest you or [open a new one](https://github.com/P1ayer-1/Libtorch-UE5/issues/new).
3. **Make Your Changes:** Work on the issue in your local environment.
4. **Submit a Pull Request:** Push your changes to your fork and [open a pull request](https://github.com/P1ayer-1/Libtorch-UE5/compare) against our repository.




### Submitting changes

Please send a [GitHub Pull Request to LibTorch-UE5](https://github.com/P1ayer-1/Libtorch-UE5/compare) with a clear list of what you've done (read more about [pull requests](http://help.github.com/pull-requests/)).
Please follow our coding conventions (below) and make sure all of your commits are atomic (one feature per commit).

Always write a clear log message for your commits. Optionally, you can include a paragraph on background and rationale.
An example of background information is: `A description of a conversation you had on the Discord server that inspired you to create the feature.`
An example of rationale: `This pr provides a foundation for integrating speculative decoding.`

One-line messages are fine for small changes, but bigger changes should look like this:

    $ git commit -m "A brief summary of the commit
    > 
    > A paragraph describing what changed and its impact.
    > 
    > A paragraph describing relevant background information and/or why you are opening the Pull Request (If applicable)."

### Coding conventions

Start reading our code and you'll get the hang of it:

  * **Indentation:** We indent using four spaces (standard tabs)
  * **Code Style:** Follow [Unreal Engine's coding standards](https://dev.epicgames.com/documentation/en-us/unreal-engine/epic-cplusplus-coding-standard-for-unreal-engine)
  * **Separation of Concerns:** Keep logic out of views as much as possible; utilize Unreal Engine's helper functions.
  * **Working with others:** This is open-source software. You should remember that other people will read your code, and try to make it look nice for them.


## Community and Communication

Becoming part of the community means more than just code contributions. Whether you're seeking help, discussing new features, or sharing your work, communication is key.
We invite you to join our [Discord server](https://discord.gg/AWWECeRcyX) to connect with fellow contributors, get assistance, and share insights. 


## Acknowledgments

We value every contribution, and we thank you for your efforts. 

Special thanks to [Kaya Adrian](https://github.com/bUsernameIsUnavailable), the founder of this repo.
