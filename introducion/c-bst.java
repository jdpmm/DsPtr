class Node {
    private Node left;
    private Node right;
    private int value;
    private Node parent;

    public Node (int value, Node left, Node right, Node parent)
    {
        this.value  = value;
        this.left   = left;
        this.right  = right;
        this.parent = parent;
    }

    /*
     * Getters
     * */
    public Node get_left   () { return this.left; }
    public Node get_right  () { return this.right; }
    public int get_value   () { return this.value; }
    public Node get_parent () { return this.parent; }

    /*
     * Setters
     * */
    public void set_left (Node new_left)     { this.left = new_left; }
    public void set_right (Node new_right)   { this.right = new_right; }
    public void set_value (int new_value)    { this.value = new_value; }
    public void set_parent (Node new_parent) { this.parent = new_parent; }
    public static void set_parent_to_children (Node left_child, Node right_child, Node ths_parent) {
        if ( left_child != null ) { left_child.set_parent(ths_parent); }
        if ( right_child != null ) { right_child.set_parent(ths_parent); }
    }
}

public class Bst {
    public static Node bst_make_node (int value, Node left, Node right, Node parent)
    {
        return new Node(value, left, right, parent);
    }

    public static void bst_push (Node root, int value)
    {
        if ( root.get_value() == value ) {
            System.out.println("A binary search tree could not have the same value twice: " + value + ".");
            return;
        }
        if ( value > root.get_value() ) {
            if ( root.get_right() == null ) {
                root.set_right(bst_make_node(value, null, null, root));
            } else {
                bst_push(root.get_right(), value);
            }
        }
        else {
            if ( root.get_left() == null ) {
                root.set_left(bst_make_node(value, null, null, root));
            } else {
                bst_push(root.get_left(), value);
            }
        }
    }

    public static void bst_print (Node root)
    {
        if ( root.get_parent() == null ) {
            System.out.println("root: " + root.get_value());
        }
        if ( root.get_left() != null ) {
            System.out.print(root.get_left().get_value() + " <- ");
        } else {
            System.out.print("null <- ");
        }

        System.out.print(root.get_value());

        if ( root.get_right() != null ) {
            System.out.println(" -> " + root.get_right().get_value());
        } else {
            System.out.println(" -> null");
        }

        if ( root.get_left() != null ) { bst_print(root.get_left()); }
        if ( root.get_right() != null ) { bst_print(root.get_right()); }
    }

    public static Node bst_getnode (Node root, int to_find)
    {
        if ( root == null )                { return null; }
        if ( root.get_value() == to_find ) { return root; }
        if ( to_find > root.get_value() )  { return bst_getnode(root.get_right(), to_find); }
        if ( to_find < root.get_value() )  { return bst_getnode(root.get_left(), to_find); }
        return null;
    }

    public static void bst_remove (Node root, int value)
    {
        Node rm_node = bst_getnode(root, value);
        if ( rm_node == null ) {
            System.out.println(value + " could not be deleted because it doesn't exist.");
            return;
        }

        char Tnode = '>';
        if ( rm_node.get_parent() == null ) { Tnode = '*'; }
        else {
            if ( rm_node.get_parent().get_left() != null ) {
                if ( rm_node.get_parent().get_left().get_value() == value ) {
                    Tnode = '<';
                }
            }
        }

        if ( rm_node.get_left() == rm_node.get_right() ) {
            if ( Tnode == '*' ) {
                System.out.println("There is only one node, could not be deleted");
                return;
            }
            if ( Tnode == '<' ) { rm_node.get_parent().set_left(null); }
            if ( Tnode == '>' ) { rm_node.get_parent().set_right(null); }
        }
        else if ( rm_node.get_left() != null && rm_node.get_right() == null ) {
            if ( Tnode == '*' ) {
                root.set_value(root.get_left().get_value());
                root.set_right(root.get_left().get_right());
                root.set_left(root.get_left().get_left());
                Node.set_parent_to_children(root.get_left(), root.get_right(), root);
                return;
            }
            rm_node.get_left().set_parent(rm_node.get_parent());
            if ( Tnode == '>' ) { rm_node.get_parent().set_right(rm_node.get_left()); }
            else { rm_node.get_parent().set_left(rm_node.get_left()); }
        }
        else if ( rm_node.get_left() == null && rm_node.get_right() != null ) {
            if ( Tnode == '*' ) {
                root.set_value(root.get_right().get_value());
                root.set_left(root.get_right().get_left());
                root.set_right(root.get_right().get_right());

                Node.set_parent_to_children(root.get_left(), root.get_right(), root);
                return;
            }
            rm_node.get_right().set_parent(rm_node.get_parent());
            if ( Tnode == '>' ) { rm_node.get_parent().set_right(rm_node.get_right()); }
            else { rm_node.get_parent().set_left(rm_node.get_right()); }
        }
        else {
            Node min = rm_node.get_right();
            int lvls = 0;
            while ( min.get_left() != null ) {
                min = min.get_left();
                lvls++;
            }

            rm_node.set_value(min.get_value());
            if ( lvls == 0 ) {
                if ( min.get_right() != null ) {
                    min.get_right().set_parent(rm_node);
                    rm_node.set_right(min.get_right());
                }
                else {
                    min.get_parent().set_right(null);
                }
            }
            else {
                min.get_parent().set_left(null);
            }
        }
    }

    public static void main(String[] args)
    {
        Node root2 = bst_make_node(50, null, null, null);
        bst_push(root2, 80);
        bst_push(root2, 90);
        bst_push(root2, 70);
        bst_push(root2, 60);
        bst_push(root2, 75);

        bst_push(root2, 20);
        bst_push(root2, 10);
        bst_push(root2, 40);
        bst_push(root2, 30);

        bst_remove(root2, 20);
        bst_remove(root2, 30);
        bst_print(root2);
    }
}