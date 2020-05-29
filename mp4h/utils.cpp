#include "utils.hpp"
#include "make_tree.hpp"


using namespace std;

int target_glb = 0;
bool done;
TreeNode* ret;
int covered_levels = 0 ; 
#define SWITCH_TO_SERIAL_FACTOR  4


// void* parallel_search_thread_wrapper(void *arg);

TreeNode* recursive_helper(TreeNode* root, int target) {
    TreeNode* retL;
    TreeNode* retR;
    // base case; return NULL when root is NULL
    if(root == NULL) {
        return NULL;
    }

    // if root's value equals target, return root
    if(root->get_val() == target) {
        return root;
    }

    // searching on the left side of current node
    retL = recursive_helper(root->left, target);

    // check if root left value is NULL, if this is the case, go the right branch of root
    if(retL == NULL) {
        // target not found in left branch of current node, so search on the right branch of current node
        retR = recursive_helper(root->right, target);
    }

    // if left branch is not NULL, we have found the target in the left branch of current node, stop searching tree!
    if(retL != NULL) {
        return retL;
    }

    // if right branch is not NULL, we have found the target in the right branch of current node, stop searching tree!
    if(retR != NULL) {
        return retR;
    }

    return NULL;
}

TreeNode* recursive_helper_parallel(TreeNode* root) {
    
    pthread_t thread1;
    pthread_t thread2;
    TreeNode* retLeft;
    TreeNode* retRight;
    TreeNode *retSR ;
    
    covered_levels++ ; 

    // printf("IN PARALELL covered_levels = %d \n", covered_levels) ;

    if(root == NULL) {
        // root is NULL calling thread exit, which means we return from this thread with return value of root (which is NULL)
        covered_levels-- ;
        pthread_exit((void*) root);
    }

    // generate threads for the root, left, and right subtrees
    if(root->get_val() == target_glb) {
        // set done flag to true and exiting the thread with the return value of root (which contains target_glb)
        done = true;
        covered_levels-- ;
        pthread_exit((void*) root);
    }
    
    // search further only if done is false
    if(done == false) {
        if ( covered_levels <= SWITCH_TO_SERIAL_FACTOR ) {
            // printf("LEFT - THREAD ; covered_levels = %d \n", covered_levels) ;
            // Spawn thread.
            // searching on the left branch of current node
            pthread_create(&thread1, NULL, parallel_search_thread_wrapper, (void*)root->left);
            // wait for the left thread to finish and collect the result of the thread in retLeft
            pthread_join(thread1, (void**)&retLeft);
        } else {
            // printf("LEFT - CALLING SERIAL ; covered_levels = %d \n", covered_levels) ;
            // Call recursive_helper.
            // Return either NULL or a found node.
            retSR = recursive_helper(root->left , target_glb) ;
            if ( retSR != NULL) {
                // Found the element in recursive_helper call, so set done to true.
                done = true ;
                covered_levels-- ; 
                pthread_exit(retSR) ;
            }
            // covered_levels-- ;
            // return retSR ;
            // covered_level-- ; 
            // pthread_exit(retSR) ;
        }

        
    }
    
    if(done == false) {

        if ( covered_levels <= SWITCH_TO_SERIAL_FACTOR ) {
            // Spawn thread.
            // we are here because we did not find the target on the left branch of current node
            // so, search for target on this node's right branch
            // searching on the right branch of the current node
            pthread_create(&thread2, NULL, parallel_search_thread_wrapper, (void*)root->right);
            // wait for the right thread to finish and collect the result of the thread in retRight
            pthread_join(thread2, (void**)&retRight);

        } else {
            // Call recursive_helper.
            // Return either NULL or a found node.
            retSR = recursive_helper(root->right , target_glb) ;
            if ( retSR != NULL) {
                // Found the element in recursive_helper call, so set done to true.
                done = true ;
                covered_levels-- ; 
                pthread_exit(retSR) ;

            }
            // covered_levels-- ;
            // return retSR ;
        }
    }
    else {
        covered_levels-- ;
        // done is true, here because we found target's value in the left branch of the current node
        // so, stop searching in the entire branch and return current node's left branch's result
        pthread_exit((void*) retLeft);
    }
    
    // we are here because target was not found on the left branch of current node
    // but we spawned the right branch's search, which is what we need to check for here 
    if(done == true) {
        covered_levels-- ;
        // so, stop searching in the entire branch and return current node's right branch's result
        pthread_exit((void*) retRight);
    }

    // we reached here because target was not found on either current node's left OR right branch
    // so we terminate this thread and return NULL with pthread_exit
    covered_levels-- ;
    pthread_exit((void*) NULL);
}

TreeNode* Utils::search(TreeNode* root, int target) {
    return recursive_helper(root, target);
}

void* parallel_search_thread_wrapper(void *arg) {
    return recursive_helper_parallel((TreeNode*)arg);
}


TreeNode* Utils::search_parallel(TreeNode* root, int target) {
    TreeNode* finalSP;
    pthread_t thread;

    // setting global variable value to target value
    target_glb = target;
    // setting done flag to false
    done = false;

    // searching for target value
    pthread_create(&thread, NULL, parallel_search_thread_wrapper, (void*) root);
    pthread_join(thread, (void**)&finalSP);

    // returning from search_parallel
    ret = finalSP;
    
    return ret;
}
