#include "screen_manager.hpp"

void ScreenManager::add(const std::string& id, IScreen* screen)
{
    m_screens[id] = screen;
}

void ScreenManager::switchTo(const std::string& id)
{
    auto* next = m_screens.at(id);

    if(next->LazyInit && !m_initialized.count(id))
    {
        next->Init();
        m_initialized.insert(id);
    }
    m_current = next;
}


void ScreenManager::InitAll()
{
    for(auto& [id, screen] : m_screens)
    {
        if(!screen->LazyInit) { screen->Init(); }
    }
}

void ScreenManager::Update()
{
    if(!m_current) return;
    m_current->Update();

    if(!m_current->nextScreen.empty())
    {
        switchTo(m_current->nextScreen);
        m_current->nextScreen.clear();
    }
}

void ScreenManager::Draw()
{
    if(m_current) m_current->Draw();
}
