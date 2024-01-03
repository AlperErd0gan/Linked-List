#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TP03.h"

////////// Singly Linked List ////////

struct linearNode *createLinearNode(int id, char childName[], char parentName[], int childBY, int parentPhone)
{ // We gotta allocate some memeory with malloc for the linearNode object and than copy the data we want to include
  // We use strcpy for setting the string type data
    struct linearNode *new = (struct linearNode *)malloc(sizeof(struct linearNode));
    new->id = id;
    new->childBY = childBY;
    new->parentPhone = parentPhone;
    strcpy(new->childName, childName);
    strcpy(new->parentName, parentName);
    new->linearNext = NULL;
    return new;
}

void SL_insertBeginning(struct linearNode **head, int id, char childName[], char parentName[], int childBY, int parentPhone)
{ // We directly inserting it in the begining and updating the head pointer
    struct linearNode *new_node = createLinearNode(id, childName, parentName, childBY, parentPhone);
    new_node->linearNext = *head;
    *head = new_node;
}

void SL_insertAtEnd(struct linearNode **head, int id, char childName[], char parentName[], int childBY, int parentPhone)
{ // Create the new node with the previous function we wrote
    struct linearNode *new_node = createLinearNode(id, childName, parentName, childBY, parentPhone);
    if (*(head) == NULL)
    { // We can directly handle the case where the list is empty saving us some time and memeory
        *(head) = new_node;
        new_node->linearNext = NULL;
        return;
    }
    // Other than that we gotta find the ending node and gotta insert the new node of ours in to the list
    struct linearNode *temp = *(head);
    while (temp->linearNext != NULL)
    {
        temp = temp->linearNext;
    }
    temp->linearNext = new_node;
    new_node->linearNext = NULL;
}

void SL_insertAfterNode(struct linearNode *prevNode, struct linearNode *newNode)
{
    if (prevNode == NULL)
    {
        printf("Previous node cannot be NULL\n");
        return;
    }
    // We insert it the new node between previous node and his next
    newNode->linearNext = prevNode->linearNext;
    prevNode->linearNext = newNode;

    // TODO
    // printf("Previous node cannot be NULL\n");
}

void SL_deleteAtBeginning(struct linearNode **head)
{
    // TODO
    if (*head == NULL)
    {
        printf("List is empty, cannot delete.\n");
        return;
    }
    // We delete the head and with the help of the temperory array and update the head
    struct linearNode *temp = *head;
    *head = temp->linearNext;
    free(temp);
}

void SL_deleteAtEnd(struct linearNode **head)
{
    // TODO
    if (*(head) == NULL)
    {
        printf("List is empty, cannot delete.\n");
        return;
    }
    if ((*(head))->linearNext == NULL)
    {
        // If there's only one node in the list, delete it and with that we handle this case in case of getting a memory leak
        free(*head);
        *head = NULL;
        return;
    }
    // Here we crrated a end pointer to keep the end of the list
    // And we create the temp to go trough the list
    struct linearNode *temp = *(head);
    struct linearNode *end = NULL;
    while (temp->linearNext->linearNext != NULL)
    {
        temp = temp->linearNext;
    }
    end = temp->linearNext;
    temp->linearNext = NULL;
    free(end);
}

void SL_deleteAfterNode(struct linearNode *head, int targetID)
{
    if (head == NULL)
    {
        printf("List is empty, cannot delete.\n");
        return;
    }
    // NodeToDelete will keep the node ew wanna delete
    struct linearNode *temp = head;
    struct linearNode *nodeToDelete = NULL;
    while (temp->linearNext != NULL)
    {
        if (temp->id == targetID)
        { // If the target node is achieved we get the nodeToDelete and we delete it

            nodeToDelete = temp->linearNext;
            temp->linearNext = nodeToDelete->linearNext;
            free(nodeToDelete);
            return;
        }

        temp = temp->linearNext;
    }

    // TODO
    // printf("List is empty, cannot delete.\n");
    // printf("Node with ID %d not found in the list, cannot delete.\n", targetID);
}

void printSinglyLinearList(struct linearNode *head)
{
    struct linearNode *current = head;
    if (head == NULL)
    {
        printf("List is empty.\n");
    }
    else
    { // we use current != NULL to also get the end element
        while (current != NULL)
        { // We run in the list and print all the elements
            printf("ID: %d, Child Name: %s, Parent Name: %s, Child Birth Year: %d, Parent Phone: %d\n", current->id, current->childName, current->parentName, current->childBY, current->parentPhone);
            current = current->linearNext;
        }
    }

    // TODO
    // printf("List is empty.\n");
    // printf("ID: %d, Child Name: %s, Parent Name: %s, Child Birth Year: %d, Parent Phone: %d\n", current->id, current->childName, current->parentName, current->childBY, current->parentPhone);
}

struct linearNode *searchSinglyNode(struct linearNode *head, int id)
{
    struct linearNode *found = NULL;
    if (head == NULL)
    {
        printf("List is empty.\n");
        return found;
    }

    struct linearNode *temp = head;
    // Same logic for the print function and we do the same in order to get the last element of the list.
    while (temp != NULL)
    {
        if (temp->id == id)
        {
            // Node with the specified ID is found, no need to continue searching.
            found = temp;
            break;
        }

        temp = temp->linearNext;
    }

    if (found == NULL)
    {
        // Node with the specified ID was not found,so print the message and show that it is not found
        printf("Node with ID %d not found in the list.\n", id);
    }

    return found;
    // TODO
    // printf("List is empty.\n");
    // printf("Node with ID %d not found in the list.\n", id);
}

////////// Circular Singly Linked List ////////

void CSL_insertBeginning(struct linearNode **head, int id, char childName[], char parentName[], int childBY, int parentPhone)
{
    struct linearNode *new = createLinearNode(id, childName, parentName, childBY, parentPhone);

    if (*head == NULL)
    {
        // If the list is initially empty, set the new node as the head. Helpful to get away from the case where the list is empty
        new->linearNext = new;
        *head = new;
        return;
    }
    // Find the end and link the new element to the beginning of the list
    struct linearNode *temp = *head;
    while (temp->linearNext != *head)
    {
        temp = temp->linearNext;
    }
    new->linearNext = *head;
    *head = new;
    temp->linearNext = new;
}

void CSL_insertAtEnd(struct linearNode **head, int id, char childName[], char parentName[], int childBY, int parentPhone)
{
    struct linearNode *new = createLinearNode(id, childName, parentName, childBY, parentPhone);
    if (*head == NULL)
    {
        new->linearNext = new; // Make it point to itself to form a circular list, the case where the list empty initially
        *head = new;
        return;
    }
    else
    {
        struct linearNode *temp = *head;
        while (temp->linearNext != *head)
        {
            temp = temp->linearNext;
        }
        temp->linearNext = new;
        new->linearNext = *head;
    }
}

void CSL_insertAfterNode(struct linearNode *prevNode, struct linearNode *newNode)
{
    // TODO
    // printf("Previous node cannot be NULL\n");
    if (prevNode == NULL)
    {
        printf("Previous node cannot be NULL\n");
        return;
    }
    // If node after the prevNode is NULL we can get some segmentation faults so we gotta check this case
    if (prevNode->linearNext == NULL)
    {
        prevNode->linearNext = newNode;
        newNode->linearNext = NULL;
        return;
    }
    newNode->linearNext = prevNode->linearNext;
    prevNode->linearNext = newNode;
}

void CSL_deleteAtBeginning(struct linearNode **head)
{
    if (*(head) == NULL)
    {
        printf("List is empty, cannot delete.\n");
        return;
    }

    struct linearNode *temp = *(head);
    struct linearNode *ind = *(head);
    if (temp->linearNext == *head)
    {
        // If there is only one node in the circular list we delete it
        free(temp);
    }
    // Search the end element and insert delete in the begining in order to link the new head to the end we find end
    while (temp->linearNext != *head)
    {
        temp = temp->linearNext;
    }
    *(head) = (*(head))->linearNext;
    temp->linearNext = (*head);
    free(ind);

    // TODO
    // printf("List is empty, cannot delete.\n");
}

void CSL_deleteAtEnd(struct linearNode **head)
{
    if (*(head) == NULL)
    {
        printf("List is empty, cannot delete.\n");
        return;
    }

    struct linearNode *temp = *head;
    struct linearNode *end = NULL;
    // We check the case where there is only the head element of the list
    if (temp->linearNext == *head)
    {
        // If there is only one node in the circular list we delete it in order to not get into bad memeory situations
        free(temp);
        *head = NULL;
        return;
    }
    // Stop at the element before end element
    while (temp->linearNext->linearNext != *head)
    {
        temp = temp->linearNext;
    }
    // Find and keep the end element in a variable and than we will delete it and link the previous element to the head
    end = temp->linearNext;
    end->linearNext = NULL;
    temp->linearNext = *head;

    free(end);
    // TODO
    // printf("List is empty, cannot delete.\n");
}

void CSL_deleteAfterNode(struct linearNode *head, int targetID)
{
    if (head == NULL)
    {
        printf("List is empty, cannot delete.\n");
        return;
    }
    struct linearNode *temp = head;
    struct linearNode *deleteThis = NULL;
    // Go trought the list in order to find the element with terget id
    // If we found it we will delete the node after it

    while (temp->linearNext != head)
    {
        if (temp->id == targetID)
        {
            deleteThis = temp->linearNext;
            temp->linearNext = deleteThis->linearNext;
            free(deleteThis);
            return;
        }
        temp = temp->linearNext;
    }
    // The loop doesn't look for the element at the and so we gotta check it after the loop
    if (temp->id == targetID)
    {
        deleteThis = temp->linearNext;
        temp->linearNext = head; // Update the last node's link to point to the new head.
        free(deleteThis);
        return;
    }
    // Print the message if the function didn't already ended
    printf("Node with ID %d not found in the list, cannot delete.\n", targetID);
}
struct linearNode *searchCircularSinglyNode(struct linearNode *head, int id)
{
    struct linearNode *found = NULL;
    if (head == NULL)
    {
        printf("List is empty, cannot delete.\n");
        return found;
    }

    struct linearNode *temp = head;
    // We gotta use do-while in order traverse through all elements of the list so if we used while one element wouldn't get checked out
    do
    {
        if (temp->id == id)
        {
            found = temp;
            break;
        }
        temp = temp->linearNext;
    } while (temp != head);
    // Found is still NULL so we can print the message knowing that it is not in the list
    if (found == NULL)
    {
        printf("Node with ID %d not found in the list.\n", id);
    }
    return found;

    // TODO
    // printf("List is empty.\n");
    // printf("Node with ID %d not found in the list.\n", id);
}

void printSinglyCircularList(struct linearNode *head)
{
    if (head == NULL)
    {
        printf("List is empty, cannot delete.\n");
        return;
    }
    // Print the list using current pointer we print one more time after loop because the end element can't go through the loop
    struct linearNode *current = head;
    while (current->linearNext != head)
    {
        printf("ID: %d, Child Name: %s, Parent Name: %s, Child Birth Year: %d, Parent Phone: %d\n", current->id, current->childName, current->parentName, current->childBY, current->parentPhone);
        current = current->linearNext;
    }
    printf("ID: %d, Child Name: %s, Parent Name: %s, Child Birth Year: %d, Parent Phone: %d\n", current->id, current->childName, current->parentName, current->childBY, current->parentPhone);

    // TODO
    // printf("List is empty.\n");
    // printf("ID: %d, Child Name: %s, Parent Name: %s, Child Birth Year: %d, Parent Phone: %d\n", current->id, current->childName, current->parentName, current->childBY, current->parentPhone);
}

////////// Doubly Linked List ////////

// Function to create a node for the circular doubly linked list
struct doublyNode *createDoublyNode(int id, char childName[], char parentName[], int childBY, int parentPhone)
{ // We create the doublyNode with next and Perivious pointers and with the help of strcpy function
    struct doublyNode *new = (struct doublyNode *)malloc(sizeof(struct doublyNode));
    new->childBY = childBY;
    new->parentPhone = parentPhone;
    strcpy(new->childName, childName);
    strcpy(new->parentName, parentName);
    new->id = id;
    new->doublyNext = NULL;
    new->doublyPrev = NULL;
    return new;
}

void DL_insertBeginning(struct doublyNode **head, int id, char childName[], char parentName[], int childBY, int parentPhone)
{
    struct doublyNode *newNode = createDoublyNode(id, childName, parentName, childBY, parentPhone);
    newNode->doublyNext = *(head);
    newNode->doublyPrev = NULL;
    // If head is NULL we check for a special case
    if (*head != NULL)
    {
        (*(head))->doublyPrev = newNode;
    }
    *(head) = newNode;
}

void DL_insertAtEnd(struct doublyNode **head, int id, char childName[], char parentName[], int childBY, int parentPhone)
{
    struct doublyNode *newNode = createDoublyNode(id, childName, parentName, childBY, parentPhone);
    struct doublyNode *current = *head;

    if (*head == NULL)
    {
        // If the list is empty, make the new node the head, we better check in order to not go through the list if the list is already empty
        *head = newNode;
        return;
    }

    while (current->doublyNext != NULL)
    {
        current = current->doublyNext;
    }
    // We insert it at end and make the new node's next pointer point to NULL
    current->doublyNext = newNode;
    newNode->doublyPrev = current;
    newNode->doublyNext = NULL;
}

void DL_insertAfterNode(struct doublyNode *prevNode, struct doublyNode *newNode)
{
    if (prevNode == NULL)
    {
        printf("Previous node cannot be NULL.\n");
        return;
    }
    if (prevNode->doublyNext == NULL)
    { // Speacial case check if the prevNode's next node is empty which means the prevNode is the ending of the list
        prevNode->doublyNext = newNode;
        newNode->doublyPrev = prevNode;
        newNode->doublyNext = NULL;
        return;
    }
    // If the prevNode is not in the end we do the thing we would've already done
    prevNode->doublyNext->doublyPrev = newNode;
    newNode->doublyNext = prevNode->doublyNext;
    prevNode->doublyNext = newNode;
    newNode->doublyPrev = prevNode;

    // TODO
    // printf("Previous node cannot be NULL.\n");
}

void DL_deleteAtBeginning(struct doublyNode **head)
{
    if (*(head) == NULL)
    {
        printf("List is empty, cannot delete.\n");
        return;
    }
    struct doublyNode *temp = *head;
    *head = temp->doublyNext;
    if (temp->doublyNext != NULL)
    { // If there is only one element in the list which is head
        temp->doublyNext->doublyPrev = NULL;
    }
    free(temp);

    // TODO
    // printf("List is empty, cannot delete.\n");
}

void DL_deleteAtEnd(struct doublyNode **head)
{
    if (*(head) == NULL)
    {
        printf("List is empty, cannot delete.\n");
        return;
    }
    struct doublyNode *current = *head;
    while (current->doublyNext != NULL)
    {
        current = current->doublyNext;
    }
    if (current->doublyPrev != NULL)
    { // We free the current from the list it self and check if his perivious node is NULL which would be illegal
        current->doublyPrev->doublyNext = NULL;
    }

    free(current);
    // TODO
    // printf("List is empty, cannot delete.\n");
}

void DL_deleteAfterNode(struct doublyNode *head, int targetID)
{
    if (head == NULL)
    {
        printf("List is empty, cannot delete.\n");
        return;
    }
    struct doublyNode *current = head;
    // While loop to go through all thr elements
    // We check each itteration for the target id and if we found we delete its after element
    // We gotta check if the node we wanna delete has a next element or not beacause iy changes cases
    while (current != NULL)
    {
        if (current->id == targetID)
        {
            struct doublyNode *nodeToDelete = current->doublyNext;

            if (nodeToDelete != NULL)
            {
                current->doublyNext = nodeToDelete->doublyNext;

                if (nodeToDelete->doublyNext != NULL)
                {
                    nodeToDelete->doublyNext->doublyPrev = current;
                }

                nodeToDelete->doublyPrev = NULL;
                nodeToDelete->doublyNext = NULL;
                free(nodeToDelete);
                return; // Exit the function after deleting the node succsesfully
            }
            else
            {
                printf("Node with ID %d not found in the list, cannot delete.\n", targetID);
                return; // if that node is null than we are at the end of the list. It is a very tricky situation for the deletion after.
            }
        }

        current = current->doublyNext;
    }

    printf("Node with ID %d not found in the list, cannot delete.\n", targetID);
}
// TODO
// printf("List is empty, cannot delete.\n");
// printf("Node with ID %d not found in the list, cannot delete.\n", targetID);

void printDoublyLinearList(struct doublyNode *head)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    struct doublyNode *current = head;
    while (current != NULL)
    { // Print all the elements witgh the help of the loop
        printf("ID: %d, Child Name: %s, Parent Name: %s, Child Birth Year: %d, Parent Phone: %d\n", current->id, current->childName, current->parentName, current->childBY, current->parentPhone);
        current = current->doublyNext;
    }
    // TODO
    // printf("List is empty.\n");
    // printf("ID: %d, Child Name: %s, Parent Name: %s, Child Birth Year: %d, Parent Phone: %d\n", current->id, current->childName, current->parentName, current->childBY, current->parentPhone);
}

struct doublyNode *searchDoublyNode(struct doublyNode *head, int id)
{
    struct doublyNode *found = NULL;
    if (head == NULL)
    {
        printf("List is empty.\n");
        return found;
    }
    struct doublyNode *current = head;
    // Without putting current->next we also look into the ending element which is very important but it can be also implamented differently
    // For exemple I have done the same thing in the CSL function but in the print I used an another print after the loop in order to print the last element
    while (current != NULL)
    {
        if (current->id == id)
        {
            found = current;
            break;
        }
        current = current->doublyNext;
    }
    if (found == NULL)
    {
        printf("Node with ID %d not found in the list.\n", id);
    }

    return found;
}
// TODO
// printf("List is empty.\n");
// printf("Node with ID %d not found in the list, cannot delete.\n", targetID);

/////// Circular Doubly Linked List /////////////

void CDL_insertBeginning(struct doublyNode **head, int id, char childName[], char parentName[], int childBY, int parentPhone)
{
    struct doublyNode *new = createDoublyNode(id, childName, parentName, childBY, parentPhone);
    // If the list is empty we check for this special situation
    if (*head == NULL)
    {
        // If the list is empty, make 'new' the only node in the list.
        new->doublyPrev = new;
        new->doublyNext = new;
        *head = new; // Update the head to point to the new node.
        return;
    }
    // Else we do it differently so the implementation changes
    else
    {
        // Insert new at the beginning.
        new->doublyNext = *head;
        new->doublyPrev = (*head)->doublyPrev;
        (*head)->doublyPrev->doublyNext = new;
        (*head)->doublyPrev = new;
        *head = new; // Update the head to point to the new node.
    }
}

void CDL_insertAtEnd(struct doublyNode **head, int id, char childName[], char parentName[], int childBY, int parentPhone)
{
    struct doublyNode *new = createDoublyNode(id, childName, parentName, childBY, parentPhone);

    if (*head == NULL)
    { // Same thing with the insert begining function
        // If the list is empty, make new the only node in the list.
        new->doublyPrev = new;
        new->doublyNext = new;
        *head = new; // Update the head to point to the new node.
        return;
    }
    else
    {
        // Insert new at the end.
        new->doublyPrev = (*head)->doublyPrev;
        new->doublyNext = *head;
        (*head)->doublyPrev->doublyNext = new;
        (*head)->doublyPrev = new;
    }
}

void CDL_insertAfterNode(struct doublyNode *prevNode, struct doublyNode *newNode)
{
    if (prevNode == NULL)
    {
        printf("Previous node cannot be NULL.\n");
        return;
    }
    // we insert the element between to nodes it includes the case where we are in the ending because we are in a circular list
    newNode->doublyNext = prevNode->doublyNext;
    newNode->doublyPrev = prevNode;
    prevNode->doublyNext = newNode;

    if (newNode->doublyNext != NULL)
    {
        newNode->doublyNext->doublyPrev = newNode;
    }

    // TODO
    // printf("Previous node cannot be NULL.\n");
}

void CDL_deleteAtBeginning(struct doublyNode **head)
{
    if (*(head) == NULL)
    {
        printf("List is empty, cannot delete.\n");
        return;
    }
    struct doublyNode *end = (*head)->doublyPrev;
    struct doublyNode *temp = *head;
    // if there is only one element in thre list
    if ((*head)->doublyNext == *head)
    {
        *head = NULL; // List becomes empty after deletion
    }
    else
    { // Else things change
        *head = (*head)->doublyNext;
        end->doublyNext = *head;
        (*head)->doublyPrev = end;
    }

    free(temp);
    // TODO
    // printf("List is empty, cannot delete.\n");
}

void CDL_deleteAtEnd(struct doublyNode **head)
{
    if (*(head) == NULL)
    {
        printf("List is empty, cannot delete.\n");
        return;
    }
    struct doublyNode *end = (*head)->doublyPrev;
    if (end == *head)
    {
        // If there's only one node in the list, we can simply delete it
        // The end and the head are the same so the case whwre we got only one element int the list
        free(end);
        *head = NULL;
    }
    else
    {
        // Else we update the doublyPrev and doublyNext pointers accordingly
        end->doublyPrev->doublyNext = *head;
        (*head)->doublyPrev = end->doublyPrev;
        free(end);
    }

    // TODO
    // printf("List is empty, cannot delete.\n");
}

void CDL_deleteAfterNode(struct doublyNode *head, int targetID)
{
    if (head == NULL)
    {
        printf("List is empty, cannot delete.\n");
        return;
    }

    struct doublyNode *temp = head;
    struct doublyNode *deleteThis = NULL;
    // Same thing that we done in the CSL
    while (temp->doublyNext != head)
    {
        if (temp->id == targetID)
        {
            struct doublyNode *deleteThis = temp->doublyNext;
            temp->doublyNext = deleteThis->doublyNext;
            deleteThis->doublyNext->doublyPrev = temp;
            deleteThis->doublyNext = NULL;
            deleteThis->doublyPrev = NULL;
            free(deleteThis);
            return;
        }
        temp = temp->doublyNext;
    }

    printf("Node with ID %d not found in the list, cannot delete.\n", targetID);

    // TODO
    // printf("List is empty, cannot delete.\n");
    // printf("Node with ID %d not found in the list, cannot delete.\n", targetID);
}

void printDoublyCircularList(struct doublyNode *head)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    struct doublyNode *current = head;
    // Here I found a rather more efficent aprroch to the issue of not including the last element of the list
    // This approch is the infinite loop that we can end from inside
    // It doesn't change anything but it is good play around this issue
    while (1)
    {
        printf("ID: %d, Child Name: %s, Parent Name: %s, Child Birth Year: %d, Parent Phone: %d\n", current->id, current->childName, current->parentName, current->childBY, current->parentPhone);
        current = current->doublyNext;

        if (current == head)
        {
            // If we've circled back to the head, we've printed all nodes
            break;
        }
    }

    // TODO
    // printf("List is empty.\n");
    // printf("ID: %d, Child Name: %s, Parent Name: %s, Child Birth Year: %d, Parent Phone: %d\n", current->id, current->childName, current->parentName, current->childBY, current->parentPhone);
}

struct doublyNode *searchCircularDoublyNode(struct doublyNode *head, int id)
{
    struct doublyNode *found = NULL;
    if (head == NULL)
    {
        printf("List is empty.\n");
        return found;
    }
    struct doublyNode *current = head;
    // Same with CSL we use the do while in order to at least traverse once from the list
    do
    {
        if (current->id == id)
        {
            found = current;
            break;
        }
        current = current->doublyNext;
    } while (current != head);

    if (found == NULL)
    {
        printf("Node with ID %d not found in the list.\n", id);
    }

    return found;
    // TODO
    // printf("List is empty.\n");
    // printf("Node with ID %d not found in the list, cannot delete.\n", targetID);
}
