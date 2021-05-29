class jobNode {
public:
    int jid;
    string cmd;
    string stat;
    int jpid;
    jobNode* next;

};
jobNode* head;
jobNode* tail;