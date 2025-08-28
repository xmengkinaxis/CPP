class Node {
	private int element;

	private int height;

	private Node left;

	private Node right;

	public Node(int element) {
		this.element = element;
		this.height = 1;
	}

	public int getElement() {
		return this.element;
	}

	public int getHeight() {
		return this.height;
	}

	public void setHeight(int height) {
		this.height = height;
	}

	public Node getLeft() {
		return this.left;
	}

	public void setLeft(Node left) {
		this.left = left;
	}

	public Node getRight() {
		return this.right;
	}

	public void setRight(Node right) {
		this.right = right;
	}
}


public class BalancedBST {

	private Node root;

	public Node getRoot() {
		return root;
	}

	public void setRoot(Node root) {
		this.root = root;
	}

	public int height(Node node) {
		if (node == null) {
			return 0;
		}
		return node.getHeight();
	}

	public int max(int a, int b) {
    	return (a > b) ? a : b;
  	}

	public Node rightRotate(Node y) {
	    Node x = y.getLeft();
    	Node z = x.getRight();
	    x.setRight(y);
    	y.setLeft(z);
	    y.setHeight(max(height(y.getLeft()), height(y.getRight())) + 1);
    	x.setHeight(max(height(x.getLeft()), height(x.getRight())) + 1);
	    return x;
  	}

  	public Node leftRotate(Node x) {
	    Node y = x.getRight();
    	Node z = y.getLeft();
	    y.setLeft(x);
    	x.setRight(z);
	    x.setHeight(max(height(x.getLeft()), height(x.getRight())) + 1);
    	y.setHeight(max(height(y.getLeft()), height(y.getRight())) + 1);
   	 	return y;
  	}

  	public int getBalanceFactor(Node node) {
	    if (node == null)
      		return 0;
    	return height(node.getLeft()) - height(node.getRight());
  	}

  	public Node insertNode(Node node, int element) {

    	if (node == null)
      		return (new Node(element));

	    if (element < node.getElement())
	      	node.setLeft(insertNode(node.getLeft(), element));
	    else if (element > node.getElement())
      		node.setRight(insertNode(node.getRight(), element));
	    else
    	  return node;

	    node.setHeight(1 + max(height(node.getLeft()), height(node.getRight())));

    	int balanceFactor = getBalanceFactor(node);
	    if (balanceFactor > 1) {
      		if (element < node.getLeft().getElement()) {
		        return rightRotate(node);
      		} else if (element > node.getLeft().getElement()) {
	        	node.setLeft(leftRotate(node.getLeft()));
	        	return rightRotate(node);
      		}
    	}
    
    	if (balanceFactor < -1) {
      		if (element > node.getRight().getElement()) {
        		return leftRotate(node);
      		} else if (element < node.getRight().getElement()) {
		        node.setRight(rightRotate(node.getRight()));
		        return leftRotate(node);
      		}
    	}
    	return node;
  	}

  	public void print(Node node) {
  		if (node != null) {
  			print(node.getLeft());
      		System.out.println(node.getElement());      
		    print(node.getRight());
    	}
  	}

  	public static void main(String args[]) {
  		BalancedBST bst = new BalancedBST();
  		bst.setRoot(bst.insertNode(bst.getRoot(), 3));
  		bst.setRoot(bst.insertNode(bst.getRoot(), 5));
  		bst.setRoot(bst.insertNode(bst.getRoot(), 1));
  		bst.setRoot(bst.insertNode(bst.getRoot(), 7));
  		bst.setRoot(bst.insertNode(bst.getRoot(), 2));

  		bst.print(bst.getRoot());
  	}
}

class HelloWorld{
	public static void main(string arg[]) {
		System.out.println("Hello, World");
	}
}

// javac foo.java
// java foo

class MyClass
{
	static private int x; 
	{ x = 5; }
	public static doStuff() {
		// do stuff
	}
}

MyClass.doStuff(); 

MyClass x = new MyClass(); 
x.doStuff(); 

class Foo extends balanceFactor{
	public void foo(); 
	public void bar(); 
}

abstract class Bar {
	public abstract void foo(); 
}

interface Bar {
	public void foo(); 
}

class Chocolate implements Bar {
	public void foo() {}
}

MyClass x = null; 
boolean foo; 
final int x = 7; 
int foo() throws IOException

int[] x = new int[10]; 

ArrayList myArrayList = new ArrayList(); 
Iterator itr = myArrayList.iterator(); 
while (itr.hasNext()) {
	System.out.println(itr.next()); 	
}

for (Object o : myArrayList) {
	System.out.println(o);
}

// int main(int argc, char* argv[]);
public static void main(String[] args); 

String[] SUITS = {"Club", "Diamonds"}; 
double[] a = new double[n]; 
a[i] = Math.random(); 
double max = Double.NEGATIVE_INFINITY; 
double[][] a; 

StdOut.printf("%7.5f", Math.PI); 

String s = new String("Hello, world"); 
char c = s.charAt(4); 
private final double rx, ry; 


public class Charge 
{
	private final double rx, ry; 
	private final double q; 
	public Charge(double x0, double y0, double q0) {
		rx = x0; ry = y0; q = q0; 
	}
}