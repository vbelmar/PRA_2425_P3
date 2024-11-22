#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
	    int nelem;
	    BSNode<T>* root;

	    T search(T e) const {
	    	return search(root, e).nelem;
	    }

	    T operator[](T e) const {
	    	return search(e);
	    }

	    void insert(T e) {
	    	root = insert(root, e);
	    }

	    friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
	   	return print_inorder(); 
	    }
	    
	    void remove(T e){
	    	root = remove(root, e);
	    }

	    ~BSTree(){
	    	delete_cascade(root);
	    }



    public:
	    BSTree() {}

	    int size() const {
	    	return nelem;
	    }

	    BSNode<T>* search(BSNode<T>* n, T e) const {
	    	if(n == NULL){
			throw std::runtime_error("Elemento no encontrado");
		}else if(n.elem < e){
			return search(n.right, e);
		}else if(n.elem > e){
			return search(n.left, e);
		}else{
			return n;
		}
	    }

	    BSNode<T>* insert(BSNode<T>* n, T e){
	    	if(n == NULL){
			return new BSNode(e);
		}else if(n.elem == e){
			throw std::runtime_error("Elemento duplicado");
		}else if(n.elem < e){
			n.right = insert(n.right, e);
		}else{
			n.left = insert(n.left, e);
		}
		return n;
	    }

	    void print_inorder(std::ostream &out, BSNode<T>* n) const{
	    	if(n != NULL){
			print_inorder(out, n->left);

			out << n->data << " ";

			print_inorder(out, n->right);
		}
	    }

	    BSNode<T>* remove(BSNode<T>* n, T e){
	    	if(n == NULL){
			throw std::runtime_error("Elemento no encontrado");
		}else if(n.elem < e){
			n.right = remove(n.right, e);
		}else if(n.elem > e){
			n.left = remove(n.left, e);
		}else{
			if(n.left != NULL && n.right != NULL){
				n.elem = max(n.left);
				n.left = remove_max(n.left);
			}else{
				n = (n.left != NULL)? n.left: n.right;
			}
		}
		return n;
	    }

	    T max(BSNode<T>* n) const{
	    	if(n == NULL){
			throw std::runtime_error("Elemento no encontrado");
		}else if(n.right != NULL){
			return max(n.right);
		}else{
			return n.elem;
		}
	    }

	    BSNode<T>* remove_max(BSNode<T>* n){
	    	if(n.right == NULL){
			return n.left;
		}else{
			n.right = remove_max(n.right);
			return n;
		}
	    }

	    void delete_cascade(BSNode<T>* n){
	 	if(n != nullptr){
			delete_cascade(n->left);

			delete_cascade(n->right);
			
			delete n;
		}
	    }
        
    
};

#endif
