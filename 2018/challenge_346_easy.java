import java.lang.String;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

// https://www.reddit.com/r/dailyprogrammer/comments/7p5p2o/20180108_challenge_346_easy_cryptarithmetic_solver/

public class challenge_346_easy
{
	// Assuming all operators are + for now
	private String[] operands;
	private String answer;

	private Map<Character, Integer> values;

	public challenge_346_easy()
	{
		;
	}

	// Parse the input in the form "BLAH + BLOB [+ ...] == BOBBY"
	// Prepare the values HashMap for calculation by working out which letters CAN'T be zero
	// (the leading letters of each part of operands)
	public void parse(String input)
	{
		String[] temp = input.split(" \\+|== ");
		operands = Arrays.copyOfRange(temp, 0, temp.length-1);
		answer = temp[temp.length-1];
		for (int i=0; i<operands.length; i++)
		{
			operands[i] = operands[i].trim();
//			System.out.print("|" + operands[i] + "|" + ", ");
		}
//		 System.out.println("|" + answer + "|");
		
		values = new HashMap<Character, Integer>();
		for (String s : operands)
		{
			for (int i=0; i<s.length(); i++)
			{
				Character c = s.charAt(i);
				values.put(c, 0);
			}
		}
		for (int i=0; i<answer.length(); i++)
		{
			Character c = answer.charAt(i);
			values.put(c, 0);
		}
	}

	// Complexity is O(26^numDistinctChars)
	public Map<Character, Integer> calculate()
	{
		int expected = createNumberFrom(answer);
		for (every possible permutation of numbers (0-9))
		{
			change the map appropriately
			
			int sum = 0;
			for (String operand : operands)
			{
				sum += createNumberFrom(operand);
			}
			if (sum == expected)
			{
				return values;
			}
		}
		return null;
	}

	// Use values to create the integer representation of s
	private int createNumberFrom(String s)
	{
		int out = 0;
		for (int i=0; i<s.length(); i++)
		{
			out += values.get(s.charAt(i));
			if (i < s.length() - 1) out *= 10;
		}
		
		return out;
	}


	public static void main(String[] args)
	{
		challenge_346_easy a = new challenge_346_easy();

		String[] inputs = {
			"THIS + IS + HIS == CLAIM",
			"WHAT + WAS + THY == CAUSE",
			"HIS + HORSE + IS == SLAIN",
			"HERE + SHE == COMES",
			"FOR + LACK + OF == TREAD",
			"I + WILL + PAY + THE == THEFT",
		};

		for (String input : inputs)
		{
			a.parse(input);
			Map<Character, Integer> values = a.calculate();
			System.out.println(values);
		}
	}
}
