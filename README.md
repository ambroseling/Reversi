# Reversi

As a final project of our introductory course to programming in C, I developed a bot that is able to play Reversi - a turn-based strategy game that is played on a board with n x n dimensions. Players lay tiles on the board that follow these rules 

1) There must be a continuous straight line of tile(s) of the opponent’s colour in at least one of the eight directions from the candidate empty position (North, South, East, West, and diagonals).
2) In the position immediately following the continuous straight line mentioned in #1 above, a tile of the player’s colour must already be placed.

For more information about how to play the game, check out [this video](https://www.google.com/search?q=hwo+to+play+reversi&sxsrf=APwXEdcJAQjcz3FnvAUCg_lNzo3bspBTxA%3A1687151904007&source=hp&ei=H-WPZPyeO46pptQP8cSpuA4&iflsig=AOEireoAAAAAZI_zMNmmERKlqUMNMIREFAt0_6v6bk6f&ved=0ahUKEwi8qqzPys7_AhWOlIkEHXFiCucQ4dUDCAs&uact=5&oq=hwo+to+play+reversi&gs_lcp=Cgdnd3Mtd2l6EAMyBwgAEIAEEAoyBwgAEIAEEAoyBwgAEIAEEAoyBwgAEIAEEAoyBwgAEIAEEAoyBwgAEIAEEAoyBwgAEIAEEAoyBwgAEIAEEAoyBwgAEIAEEAoyBggAEBYQHlAAWABglAVoAHAAeACAAT2IAT2SAQExmAEAoAECoAEB&sclient=gws-wiz#kpvalbx=_IeWPZI29ELGfptQPvs6OoAo_43)

<img width="363" alt="Screenshot 2023-06-19 at 1 28 59 AM" src="https://github.com/ambroseling/Reversi/assets/93873940/88e618c6-15d7-4c59-bd60-62a2a72eac99">


## How does it work?
In this final project, I designed a reversi artificial intelligence that operates similar to a chess engine. Using MinMax, a recursive algorithm that uses a scoring system to consider possible plays. The algorithm assumes the opponent will always choose the play that maximizes their score or winning chances and finds the lowest possible maximum score for the opponent in all possible outcomes by looking at a depth of 5. 


![image](https://github.com/ambroseling/Reversi/assets/93873940/a1e98f0a-daee-4c08-99cf-64783f1043ff)


Based on this decision-making system, my reversi bot was placed 57th among 250+ student's bots in our class and delivered promising results when it played other bots. 

## Key takeaways
This final project allowed me to learn a lot about recursion and recursive algorithms and their applications in game development and other real-world applications. It also taught me ways to deliver clean and concise code as these practices helped me foster good coding habits as a beginner.
