#include "CompWindowStart.h"
#include "Game.h"
#include "Stage.h"
#include "Context.h"
#include "CommandStage.h"

namespace bali{

CompWindowStart::CompWindowStart(Stage* stage)
    : Component(stage)
{
}

CompWindowStart::~CompWindowStart()
{
}

ReturnVal CompWindowStart::initialize(){
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
    startButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind(&CompWindowStart::doStart, this, &stage->game->ctx) );
    table->Attach(startButton, sf::Rect<sf::Uint32>(0,4,2,1), 3);

    window = sfg::Window::Create();

    window->SetTitle("Phase 3");
    window->SetRequisition(sf::Vector2f(425,300));
    window->SetPosition(sf::Vector2f(100.0f,100.0f));
    window->Add(table);

    desk.Add(window);


    //No Subscriptions in this component.
    return ReturnVal();
}
ReturnVal CompWindowStart::doWindowEvent(sf::Event & event)
{
    desk.HandleEvent(event);
    return ReturnVal();
}

ReturnVal CompWindowStart::doLocalInputs()
{
    return ReturnVal();
}
uint32_t CompWindowStart::processCommands(void* arg)
{
    //This component doesn't receive commands
    return 0;
}

ReturnVal CompWindowStart::doUpdate()
{
    processCommands(nullptr);

    desk.Update(deskUpdateClock.restart().asSeconds());

    return ReturnVal();
}

ReturnVal CompWindowStart::doDraw()
{
    Context& ctx = stage->game->ctx;
    ctx.sfGui.Display(ctx.window);
    return ReturnVal();
}

ReturnVal CompWindowStart::cleanup()
{
    return ReturnVal();
}

void CompWindowStart::doStart(Context* ctx)
{
    ctx->mp.setPlayerStartInfo(nameEntry->GetText(),
                              passEntry->GetText(),
                              atoi(std::string(portEntry->GetText()).c_str()),
                              ipEntry->GetText());

    std::cout << "Hi " << ctx->mp.getPlayerName() << std::endl;

    window->Show(false);

    stage->submitCommand(std::make_shared<CommandStage>(CommandStage::Functions::STAGEFINISH, nullptr));
}


}//end namespace bali
