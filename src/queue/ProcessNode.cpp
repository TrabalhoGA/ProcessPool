#include "../include/queue/ProcessNode.h"

ProcessNode::ProcessNode(Process* proc) : process(proc), next(nullptr) {
    // ctor
}

ProcessNode::~ProcessNode() {
    process = nullptr;
    next = nullptr;
}

Process* ProcessNode::getProcess() const {
    return process;
}

ProcessNode* ProcessNode::getNext() const {
    return next;
}

void ProcessNode::setNext(ProcessNode* nextNode) {
    next = nextNode;
}