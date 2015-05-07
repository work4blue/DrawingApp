#include "Group.hpp"
#include <exception>
#include <algorithm>

Group::Group()
{

}

Group::~Group()
{
    for (VisualEntity *visual : m_children) {
        delete visual;
    }
}

// returns index of added visual entity
int Group::add(VisualEntity *val)
{
    val->setParentGroup(this);
    m_children.push_back(val);
    int index = m_children.size() - 1;
    val->setIndex(index);

    return index;
}

void Group::draw(QPainter *painter)
{
    for (VisualEntity *visual : m_children) {
        visual->draw(painter);
    }
}

bool Group::contains(int x, int y)
{
    for (VisualEntity *visual : m_children) {
        if (visual->contains(x, y)) return true;
    }

    return false;
}

// first in order gets sent back
VisualEntity *Group::getClicked(int x, int y)
{
    // last drawn visual entity is in the most front
    for (int i = m_children.size() - 1; i >= 0; i--) {
        if (m_children[i]->contains(x, y)) return m_children[i];
    }

    return nullptr;
}
