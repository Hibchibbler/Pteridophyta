#include "CommandComponent.h"

#include "Comm.h"

namespace bali{

CommandComponent::CommandComponent(uint32_t f, Command::Arg a)
    : Command(f, a)
{

}


Command::Arg
CommandComponent::structifyWhoIsAck(CommEvent& event)
{
    std::shared_ptr<CommandComponent::WhoIsAckStruct>  wia
        = std::make_shared<CommandComponent::WhoIsAckStruct>();

    uint32_t np;
    (*event.packet) >> np;
    for (int i = 0;i < np;i++)
    {
        std::string name;
        uint32_t team;//We are not using team
        (*event.packet) >> name >> team;

        CommandComponent::WhoIsAckStruct::NameTeam nt(name,team);
        wia->names.push_back(nt);
    }
    return wia;
}

Command::Arg
CommandComponent::structifyIdAck(CommEvent& event)
{
    std::shared_ptr<CommandComponent::IdAckStruct>  wia
        = std::make_shared<CommandComponent::IdAckStruct>();

    return wia;
}




}//end namespace bali

