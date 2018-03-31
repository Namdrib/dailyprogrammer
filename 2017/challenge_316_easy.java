import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashSet;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Collections;

// Knight's Metric
public class challenge_316_easy
{
	public static class NodeDistanceComparator implements Comparator<Node>
	{
		public int compare(Node x, Node y)
		{
			return x.compareTo(y);
		}
	}

	// Combinations of knight moves when used together
	// e.g. dx[3], dy[3]
	private final int dx[] = {-1, 1, -1, 1, -2, 2, -2, 2};
	private final int dy[] = {-2, -2, 2, 2, -1, -1, 1, 1};

	public challenge_316_easy()
	{
		;
	}

	private Node dijkstra(final Coord in, final Coord out)
	{
		HashSet<Coord> closed = new HashSet<Coord>();
		PriorityQueue<Node> fringe = new PriorityQueue<Node>(10, new NodeDistanceComparator());

		Node root = new Node(in);

		fringe.add(root);

		while (!fringe.isEmpty())
		{
			Node current = fringe.poll();
			if (current == null)
			{
				break;
			}

			if (current.c.equals(out))
			{
				return current;
			}

			// System.out.println("Currently at " + current.c);

			// Try each possible move from here
			for (int i = 0; i < dx.length; i++)
			{
				Coord tempLocation = new Coord(current.c);
				tempLocation.translate(dx[i], dy[i]);

				// Already closed this location (no point visiting again)
				if (closed.contains(tempLocation))
				{
					continue;
				}

				// Update the result of stepping to new location
				Node temp = new Node(tempLocation);
				temp.parent = current;
				temp.g+=1;
				temp.setHeuristic(out);
				temp.f = temp.g + temp.h;
				// System.out.println("\tConsidering " + temp.c);

				fringe.add(temp);
				closed.add(tempLocation);
			}

			if (closed.contains(current.c))
			{
				closed.add(current.c);
			}
		}

		return null; // No path to out
	}

	public int numMovesTo(final Coord dest)
	{
		// Search the space
		Node n = dijkstra(new Coord(0, 0), dest);
		int numMoves = -1;

		if (n == null)
		{
			System.out.println("No path to " + dest);
		}
		else
		{
			List<Coord> movesMade = new ArrayList<Coord>();
			// Iterate the chain of parents
			for (Node temp = new Node(n); temp != null; temp = temp.parent)
			{
				movesMade.add(temp.c);
				numMoves++;
			}

			Collections.reverse(movesMade);
			System.out.println(movesMade);
		}

		return numMoves;
	}

	public static void main(String[] args)
	{
		challenge_316_easy a = new challenge_316_easy();

		String inputs[] = {"3 7", "7 7", "1 1", "0 0", "-31 82", "1 0", "0 1", "-1 -1"};

		for (String input : inputs)
		{
			String[] parts = input.split(" "); // assume input is of two numbers
			Coord destination = new Coord(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]));
			int out = a.numMovesTo(destination);
			System.out.println(out + " moves to " + input);
		}
	}

	public static class Coord
	{
		int x;
		int y;

		public Coord()
		{
			this(0, 0);
		}

		public Coord(int x, int y)
		{
			this.x = x;
			this.y = y;
		}

		public Coord(Coord c)
		{
			this(c.x, c.y);
		}

		public void translate(int x, int y)
		{
			this.x += x;
			this.y += y;
		}

		public boolean equals(Coord c)
		{
			return this.x == c.x && this.y == c.y;
		}

		@Override
		public String toString()
		{
			return x + "," + y;
		}
	}

	public class Node
	{
		public int f; // cost
		public int g; // running total
		public int h; // heuristic

		Coord c; // where this node is

		Node parent; // parent of this node

		Node()
		{
			this(new Coord());
		}

		Node(Coord c)
		{
			f = 0;
			g = 0;
			h = 0;
			parent = null;
			this.c = c;
		}

		Node(Node n)
		{
			this.f = n.f;
			this.g = n.g;
			this.h = n.h;
			this.c = n.c;
			this.parent = n.parent;
		}

		public void setHeuristic(Coord dest)
		{
			int deltaX = Math.abs(dest.x - c.x);
			int deltaY = Math.abs(dest.y - c.y);
			h = (deltaX + deltaY) / 4;
		}

		public int getF()
		{
			return f;
		}

		public Coord getCoord()
		{
			return c;
		}

		public boolean equals(Node n)
		{
			return this.c == n.c;
		}

		public int compareTo(Node n)
		{
			return this.f - n.f;
		}
	}

}
