#include "CompWindowStart.h"
#include "ContextClient.h"
#include "Stage.h"
#include "CommandStage.h"

namespace bali{

CompWindowStart::CompWindowStart(Stage* stage)
    : Component(stage)
{
}

CompWindowStart::~CompWindowStart()
{
}

uint32_t CompWindowStart::initialize(Context& c){
    //Construct Start Menu GUI
    sfg::Table::Ptr table( sfg::Table::Create(  ) );

    sfg::Label::Ptr nameLabel;
    nameLabel = sfg::Label::Create("Name");
    nameEntry = sfg::Entry::Create();
    nameEntry->SetRequisition(sf::Vector2f(120.0f,0.0f));
    table->Attach(nameLabel,sf::Rect<sf::Uint32>(0,0,1,1), 0);
    table->Attach(nameEntry,sf::Rect<sf::Uint32>(1,0,1,1), 3);

    sfg::Label::Ptr passLabel;
    passLabel = sfg::Label::Create("Password");
    passEntry = sfg::Entry::Create();
    table->Attach(passLabel, sf::Rect<sf::Uint32>(0,1,1,1), 0);
    table->Attach(passEntry, sf::Rect<sf::Uint32>(1,1,1,1), 3);

    sfg::Label::Ptr ipLabel;
    ipLabel = sfg::Label::Create("IP");
    ipEntry = sfg::Entry::Create();
    table->Attach(ipLabel, sf::Rect<sf::Uint32>(0,2,1,1), 0);
    table->Attach(ipEntry, sf::Rect<sf::Uint32>(1,2,1,1), 3);

    sfg::Label::Ptr portLabel;
    portLabel = sfg::Label::Create("Port");
    portEntry = sfg::Entry::Create();
    table->Attach(portLabel, sf::Rect<sf::Uint32>(0,3,1,1), 0);
    table->Attach(portEntry, sf::Rect<sf::Uint32>(1,3,1,1), 3);

    sfg::Button::Ptr startButton;
    startButton = sfg::Button::Create("Start");
    startButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind(&CompWindowStart::doStart, this, (ContextClient*)&c) );
    table->Attach(startButton, sf::Rect<sf::Uint32>(0,4,2,1), 3);

    window = sfg::Window::Create();

    window->SetTitle("Phase 3");
    window->SetRequisition(sf::Vector2f(425,300));
    window->SetPosition(sf::Vector2f(100.0f,100.0f));
    window->Add(table);

    desk.Add(window);


    //No Subscriptions in this component.
    return 0;
}
uint32_t CompWindowStart::doWindowEvent(Context& c, sf::Event & event)
{
    desk.HandleEvent(event);
    return 0;
}

uint32_t CompWindowStart::doLocalInputs(Context& c)
{
    return 0;
}
uint32_t CompWindowStart::processCommands(void* arg)
{
    //This component doesn't receive commands
    return 0;
}

uint32_t CompWindowStart::doUpdate(Context& c)
{
    ContextClient& cc = *((ContextClient*)&c);
    processCommands(nullptr);

    desk.Update(deskUpdateClock.restart().asSeconds());

    return 0;
}

uint32_t CompWindowStart::doDraw(Context& c)
{
    ContextClient& cc = *((ContextClient*)&c);
    cc.sfGui.Display(cc.window);
    return 0;
}

uint32_t CompWindowStart::cleanup(Context& c)
{
    return 0;
}

void CompWindowStart::doStart(ContextClient* cc)
{
    cc->mp.setPlayerStartInfo(nameEntry->GetText(),
                              passEntry->GetText(),
                              atoi(std::string(portEntry->GetText()).c_str()),
                              ipEntry->GetText());

    std::cout << "Hi " << cc->mp.getPlayerName() << std::endl;

    window->Show(false);

    stage->submitCommand(std::make_shared<CommandStage>(CommandStage::Functions::STAGEFINISH, nullptr));
}


}//end namespace bali
