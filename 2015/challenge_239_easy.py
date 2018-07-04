#!/usr/bin/env python3

# https://www.reddit.com/r/dailyprogrammer/comments/3r7wxz/20151102_challenge_239_easy_a_game_of_threes/

def main():
	n = int(input())

	while n > 1:
		mod = (0, 1, -1)[n % 3]
		print("{} {}".format(n, mod))
		n = int((n + mod) / 3)

	print(n)

if __name__ == '__main__':
	main()
