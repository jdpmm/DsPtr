class Node {
    private Node left;
    private Node right;
    private int value;
    final private Node parent;

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
    public void set_left (Node new_left)   { this.left = new_left; }
    public void set_right (Node new_right) { this.right = new_right; }
    public void set_value (int new_value)  { this.value = new_value; }
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


        boolean isright_child = true;
        if ( rm_node.get_parent().get_left() != null ) {
            if ( rm_node.get_parent().get_left().get_value() == value ) { isright_child = false; }
        }

        /*
         * Does not have any child
         * */
        if ( rm_node.get_left() == rm_node.get_right() ) {
            if ( isright_child ) { rm_node.get_parent().set_right(null); }
            else { rm_node.get_parent().set_left(null); }
        }
        /*
         * Only has its left child
         * */
        else if ( rm_node.get_left() != null && rm_node.get_right() == null ) {
            if ( isright_child ) {
                rm_node.get_parent().set_right(rm_node.get_left());
            } else {
                rm_node.get_parent().set_left(rm_node.get_left());
            }
        }
        /*
         * Only has its right child
         * */
        else if ( rm_node.get_left() == null && rm_node.get_right() != null ) {
            if ( isright_child ) {
                rm_node.get_parent().set_right(rm_node.get_right());
            } else {
                rm_node.get_parent().set_left(rm_node.get_right());
            }
        }
        /*
         * Has both children
         * */
        else {
            Node min_node = rm_node.get_right();
            while ( min_node.get_left() != null ) {
                min_node = min_node.get_left();
            }
            rm_node.set_value(min_node.get_value());

            System.out.println(min_node.get_value());
            if ( min_node.get_parent().get_right() != null  ) {
                if ( min_node.get_parent().get_value() == min_node.get_value() ) {
                    rm_node.set_right(min_node.get_right());
                }
            } else {
                min_node.get_parent().set_left(null);
            }
        }
    }

    public static void main(String[] args)
    {
        Node root = bst_make_node(10, null, null, null);
        bst_push(root, 5);
        bst_push(root, 15);

        bst_push(root, 3);
        bst_push(root, 4);
        bst_push(root, 1);
        bst_push(root, 2);

        bst_push(root, 7);
        bst_push(root, 6);

        bst_push(root, 12);
        bst_push(root, 16);
        bst_push(root, 11);
        bst_push(root, 13);
        bst_push(root, 19);

        bst_remove(root, 5);
        bst_print(root);
    }
}
