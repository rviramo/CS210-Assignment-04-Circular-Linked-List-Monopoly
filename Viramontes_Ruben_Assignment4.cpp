#include <iostream>
#include <string>

using namespace std;

//Monopoly Space Info
struct Space
{
    string name;
    int price;
    string owner;
};

//One Node in the linked list
struct Node
{
    //Every node contains one space
    Space space;
    Node* next;
};

struct Player
{
    string name;
    int balance;
    Node* spot;
};

class LinkedList
{
    private:
        //Points to first node in the list
        Node* head;

    public:
        //Constructor
        LinkedList()
        {
            head = nullptr;
        }

        //Returns to Start/Go
        Node* start()
        {
            return head;
        }

        //Add Node to front of linked list
        void prepend (string name, int price)
        {
            //Points to a new Node called newNode
            Node* newNode = new Node;

            newNode->space.name = name;
            newNode->space.price = price;
            newNode->space.owner = "Not Owned";
            newNode->next = nullptr;

            //new Node points to current head
            newNode->next = head;
            head = newNode;
        }

        //Add Node to end of list
        void append(string name, int price)
        {
            Node* newNode = new Node;

            newNode->space.name = name;
            newNode->space.price = price;
            newNode->space.owner = "Not Owned";
            newNode->next = nullptr;

            //If the list is empty, the NewNode is the head
            if (head == nullptr)
            {
                head = newNode;
                return;
            }
            
            Node* currNode = head;

            //Goes through the entire linked list until the last node
            while (currNode->next != nullptr)
            {
                currNode = currNode->next;
            }
            //Connects last node to the new node
            currNode->next = newNode;
        }

        //Search for a Node
        bool search(string name)
        {
            if (head == nullptr)
            {
                return false;
            }
            Node* currNode = head;

            do
            {
                if (currNode->space.name == name)
                {
                    cout <<"The Monopoly space '" << name << "' was found\n";
                    return true;
                }

                currNode = currNode->next;
            }
            while (currNode != head);

            cout << "The Monopoly space '" << name << "' was not found\n";
            return false;
            
        }

        //Remove a Node
        void remove (string name)
        {
            if (head == nullptr)
            {
                return;
            }

            if (head->space.name == name)
            {
                Node* tail = head;

                while (tail->next != head)
                {
                    tail = tail->next;
                }

                Node* delNode = head;
                head = head->next;
                tail->next = head;

                delete delNode;
                return; 
            }

            Node* currNode = head;
            do
            {
                if (currNode->next->space.name == name)
                {
                    Node* delNode = currNode->next;
                    currNode->next = delNode->next;
                    delete delNode;
                    return;
                }
                currNode = currNode->next;
            }
            while (currNode != head);
        }

        //Print all Monopoly spaces
        void print()
        {
            if (head == nullptr)
            {
                return;
            }
            Node* currNode = head;

            do
            {
                cout << "Name: " << currNode->space.name << "\n";
                cout << "Price: " << currNode->space.price << "\n";
                cout << "Owner: " << currNode->space.owner << "\n";
                cout << endl;

                currNode = currNode->next;
            }
            while (currNode !=head);
        }

        // Connects tail node back to head node
        void connectBoard()
        {
            if (head == nullptr)
            {
                return;
            }

            Node* currNode = head;
            while (currNode->next != nullptr)
            {
                currNode = currNode->next;
            }
            currNode->next = head; 
        }
};

int main ()
{
    LinkedList board;

    board.append ("GO", 0);
    board.append ("Baltic Ave", 60);
    board.append ("Oriental Ave", 100);
    board.append ("Virginia Ave", 160);
    board.append ("New York Ave", 200);
    board.append ("Indiana Ave", 220);
    board.append ("Atlantic Ave", 260);
    board.append ("Pacific Ave", 300);
    board.append ("Park Place", 350);
    board.append ("Boardwalk", 400);

    board.connectBoard();

    Player player;
    player.name = "Player 1";
    player.balance = 1500;
    player.spot = board.start();
    cout << "Starting Monopoly" << "\n";

    for (int turn = 1; turn <= 10; turn++)
    {
        cout << "Turn: " << turn << "\n";

        //Moves two spaces
        int move = 2;

        for (int i = 0; i < move; i++)
        {
            player.spot = player.spot->next;
        }
        cout << player.name << " moved to: " << player.spot->space.name << "\n";

        if (player.spot->space.price == 0)
        {
            cout << player.name << " is on GO\n";
        }
        //Player buys property not owned
        else if (player.spot->space.owner == "Not Owned")
        {
            if (player.balance >= player.spot->space.price)
            {
                player.balance = player.balance - player.spot->space.price;
                player.spot ->space.owner = player.name;
                cout << "New Balance: " << player.balance << "\n";
            }
        }
        else
        {
            cout << "This space is already owned\n";
        }
        cout << endl;
    }
   
    return 0;
}