#include "FArchive.h"

namespace upp::Readers {
    bool FArchive::HasError() const
    {
        return StoredError == Error::None;
    }

    FArchive::Error FArchive::GetError() const
    {
        return StoredError;
    }

    void FArchive::SetError(Error NewError)
    {
        StoredError = NewError;
    }

    void FArchive::ClearError()
    {
        StoredError = Error::None;
    }

    Versions::EGame FArchive::GetGame() const
    {
        return Game;
    }

    const std::string& FArchive::GetName() const
    {
        return Name;
    }

    FArchive::FArchive(Versions::EGame Game, const std::string& Name) :
        Game(Game),
        Name(Name)
    {

    }
}