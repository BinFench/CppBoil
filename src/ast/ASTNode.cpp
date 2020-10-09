#include "ASTNode.h"
#include "stringNode.cpp"
#include "chNode.cpp"
#include <type_traits>
#include <string>

template <typename... Args>
void ASTNode::populate(std::string type, ASTNode *node, Args... nodes)
{
    if (id != type)
    {
        id = type;
        link = new linkNode();
        link->attach(node);
    }
    else
    {
        linkNode *sibling = new linkNode();
        sibling->attach(node);
        link->getTail()->append(sibling);
    }
    populate(type, nodes...);
}

template <typename... Args>
void ASTNode::populate(std::string type, std::string node, Args... nodes)
{
    if (id != type)
    {
        id = type;
        link = new linkNode();
        link->attach(new stringNode(node));
    }
    else
    {
        linkNode *sibling = new linkNode();
        sibling->attach(new stringNode(node));
        link->getTail()->append(sibling);
    }
    populate(type, nodes...);
}

template <typename... Args>
void ASTNode::populate(std::string type, char node, Args... nodes)
{
    if (id != type)
    {
        id = type;
        link = new linkNode();
        link->attach(new chNode(node));
    }
    else
    {
        linkNode *sibling = new linkNode();
        sibling->attach(new chNode(node));
        link->getTail()->append(sibling);
    }
    populate(type, nodes...);
}

void ASTNode::populate(std::string type, ASTNode *node)
{
    if (id != type)
    {
        id = type;
        link = new linkNode();
        link->attach(node);
    }
    else
    {
        linkNode *sibling = new linkNode();
        sibling->attach(node);
        link->append(sibling);
    }
}

void ASTNode::populate(std::string type, std::string node)
{
    populate(type, new stringNode(node));
}

void ASTNode::populate(std::string type, char node)
{
    populate(type, new chNode(node));
}

std::string ASTNode::getId()
{
    return id;
}