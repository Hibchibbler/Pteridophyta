#include "CommandComponent.h"

#include "Comm.h"

namespace bali{

CommandComponent::CommandComponent(uint32_t f, Command::Argument::Ptr a)
    : Command(f, a)
{

}


Command::Argument::Ptr
CommandComponent::structifyWhoIsAck(CommEvent& event)
{
    //std::shared_ptr<CommandComponent::WhoIsAckStruct>  wia
    CommandComponent::WhoIsAckStruct::Ptr wia
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

Command::Argument::Ptr
CommandComponent::structifyIdAck(CommEvent& event)
{
    CommandComponent::IdAckStruct::Ptr  wia
        = std::make_shared<CommandComponent::IdAckStruct>();

    return wia;
}



}//end namespace bali

