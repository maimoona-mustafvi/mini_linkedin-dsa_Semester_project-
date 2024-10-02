#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

const int size = 15;
const int v = 10;
static int ind = 10;

struct Message {
    double timestamp;
    string content;

    Message(double timestamp, string content) {
        this->timestamp = timestamp;
        this->content = content;
    }
};

struct linkedln_user {
    string username;
    string skills[size];
    int index;
    vector<Message> messages;

    linkedln_user(string name, string skills[size], int index) {
        this->username = name;
        for (int i = 0; i < size; i++) {
            this->skills[i] = skills[i];
        }
        this->index = index;
    }
};

void heapify(vector<Message>& msg_arr, int n, int i);

bool isEmpty(linkedln_user user){
    return user.username.empty();
}

void addEdge(vector<vector<linkedln_user>>& graph, int source, int destination, linkedln_user l1, linkedln_user l2) {
    if (graph[source].empty()) {
        graph[source].push_back(l1);
    }
    graph[source].push_back(l2);

    if (graph[destination].empty()) {
        graph[destination].push_back(l2);
    }
    graph[destination].push_back(l1);
}

void bfs(vector<vector<linkedln_user>> graph, linkedln_user user, int source) {
    vector<bool> visited(v, false);
    vector<int> level(v, 0);
    queue<linkedln_user> q;

    q.push(user);
    visited[source] = true;      
    cout<<"\n******* Mini LinkedIn Project: Friend Connections and Messaging System *******\n"
        <<"\n*** Feature 1: Breadth First Search Implementation (Friend Network Levels) ***\n"            
        <<"Showing friends from 1st to 3rd levels for each member.\n\n";          

    while (!q.empty()) {
        linkedln_user u = q.front();
        q.pop();

        if (level[u.index] <= 3) {
            cout << "Visited: " << u.username << " at level " << level[u.index] << endl;
        } else {
            cout << "Visited: " << u.username << " at level others" << endl;
        }
        for (linkedln_user neigh : graph[u.index]) {             
            if (!visited[neigh.index]) {
                q.push(neigh);
                visited[neigh.index] = true;
                level[neigh.index] = level[u.index] + 1;
            }
        }
    }
}

void printGraph(vector<vector<linkedln_user>>& graph) {
    for (int i = 0; i < graph.size(); i++) {
        for (linkedln_user neigh : graph[i]) {
            if (graph[i][0].username == neigh.username) {
                continue;
            }
            cout << "Edge between " << graph[i][0].username << " and " << neigh.username << endl;
        }
        cout << endl;
    }
}

void sendMsg(Message element, int src, int dest, vector<vector<linkedln_user>>& graph) {
    if (graph[src][0].messages.size() == v) {
        cout << "Heap is full" << endl;
        return;
    } else {
        graph[src][0].messages.push_back(element);   
        int n = graph[src][0].messages.size();

        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(graph[src][0].messages, n, i);      
        }

        graph[dest][0].messages.push_back(element);
    }
}

void heapify(vector<Message>& msg_arr, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && msg_arr[left].timestamp < msg_arr[smallest].timestamp) {
        smallest = left;
    }

    if (right < n && msg_arr[right].timestamp < msg_arr[smallest].timestamp) {
        smallest = right;
    }

    if (smallest != i) {
        swap(msg_arr[i], msg_arr[smallest]);
        heapify(msg_arr, n, smallest);
    }
}

void viewMessages(vector<Message>& msg_arr){
    cout<<"\n\n*** Feature 2: Displaying Messages with Timestamps ***\n"
        <<"Messages exchanged between users are sorted by their timestamps.\n\n";
    for (Message msg : msg_arr) {
        cout << "Timestamp: " << msg.timestamp << ", Content: " << msg.content << endl;
    }
}

void createAccount(){
    string name;
    cout<<"Enter your name :";
    cin>> name;

    int n;
    cout<<"Enter number of skills you want to add :";
    cin>>n;
    
    string skills_array[n];
    for(int i=0 ; i<n ; i++){
        cin>>skills_array[i];
    }

    linkedln_user l4(name,skills_array, ind);
    ind = ind+1;
    cout<<"Linkdin user created Successfully.";
}

void search_account(vector<vector<linkedln_user>>& graph){
    string searched_name;
    cout<<"Enter username you want to Search : ";
    cin>>searched_name;

    for (int i = 0; i < graph.size(); ++i) {
            if(graph[i][0].username == searched_name){
                cout<<"User Found";
                cout<<"User Name : "<<graph[i][0].username<<endl;
                cout<<"Skills : ";
                for(int j=0; j<size ; j++ ){
                    cout<<graph[i][0].skills[j]<<" , ";
                }
                break;
            }
    }

}

void heapsort(vector<Message>& msg_arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(msg_arr, n, i);
    }


    for (int i = n - 1; i > 0; i--) {
        swap(msg_arr[0], msg_arr[i]);
        heapify(msg_arr, i, 0);
    }
}


void check_neighbours(vector<vector<linkedln_user>> &graph){
    cout<<"\n*** Feature 3: 1st Degree Friends of Each Member ***\n"
        <<"Displaying the 1st degree friends of all members.\n\n";
    for(int i=0; i<graph.size() ; i++){
        cout<<"1st Friends of "<<graph[i][0].username <<" are ";
        for(linkedln_user neigh : graph[i]){
            if(neigh.username != graph[i][0].username ){
                cout<<neigh.username <<" , ";
            }            
        }
        cout<<endl;
    }
    cout<<endl;
}

int main() {
    //createAccount();
    vector<vector<linkedln_user>> graph(v);

    string l1_skills[size] = {"Web Development", "Coding"};
    linkedln_user l1("Maimoona", l1_skills, 1);

    string l0_skills[size] = {"Software Testing", "Leadership"};
    linkedln_user l0("Iruj", l0_skills, 0);

    string l2_skills[size] = {"Machine Learning", "Data Science", "Python"};
    linkedln_user l2("Amna", l2_skills, 2);

    string l3_skills[size] = {"Java", "Spring Boot", "Microservices"};
    linkedln_user l3("Huda", l3_skills, 3);

    string l4_skills[size] = {"React", "Redux", "JavaScript"};
    linkedln_user l4("Maira", l4_skills, 4);

    string l5_skills[size] = {"C++", "Data Structures", "Algorithms"};
    linkedln_user l5("Javeria", l5_skills, 5);

    string l6_skills[size] = {"Project Management", "Agile", "Scrum"};
    linkedln_user l6("Laiba", l6_skills, 6);

    string l7_skills[size] = {"DevOps", "Docker", "Kubernetes"};
    linkedln_user l7("Mahnoor", l7_skills, 7);

    string l8_skills[size] = {"Android Development", "Kotlin", "Firebase"};
    linkedln_user l8("Moiza", l8_skills, 8);

    string l9_skills[size] = {"iOS Development", "Swift", "Xcode"};
    linkedln_user l9("Sana", l9_skills, 9);

    addEdge(graph, 0, 1, l0, l1);
    addEdge(graph, 0, 2, l0, l2);
    addEdge(graph, 0, 3, l0, l3);
    addEdge(graph, 1, 4, l1, l4);
    addEdge(graph, 1, 5, l1, l5);
    addEdge(graph, 2, 6, l2, l6);
    addEdge(graph, 2, 7, l2, l7);
    addEdge(graph, 8, 9, l8, l9);
    addEdge(graph, 7, 8, l7, l8);

    bfs(graph, l0, 0);


    Message m1(12.30, "From : IrujZulfiqar , To : Maimoona  Hey How are you?");
    Message m2(12.15, "From : IrujZulfiqar , To : Maimoona  Have you completed the assignment?");
    Message m3(14.15, "From : IrujZulfiqar , To : Maimoona  Are you free for a call later?");
    Message m4(15.45, "From : IrujZulfiqar , To : Maimoona  Can you help me with the Java project?");
    Message m5(16.30, "From : IrujZulfiqar , To : Maimoona  Don't forget about the meeting tomorrow.");
    Message m6(17.00, "From : IrujZulfiqar , To : Maimoona  Let's catch up over coffee sometime!");

    sendMsg(m1 , 0 , 1 , graph);
    sendMsg(m2 , 0 , 1 , graph);
    sendMsg(m3 , 0 , 1 , graph);
    sendMsg(m4 , 0 , 1 , graph);
    sendMsg(m5 , 0 , 1 , graph);
    sendMsg(m6 , 0 , 1 , graph);


    vector<Message> msg_arr = graph[0][0].messages;
    
    
    int s = msg_arr.size();
    heapsort(msg_arr , s);
    viewMessages(msg_arr);
     

    //search_account(graph);

    check_neighbours(graph);

    return 0;
}