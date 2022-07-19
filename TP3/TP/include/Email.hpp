#ifndef EMAIL_H
#define EMAIL_H

#include <string>
#include "msgassert.h"
#include "memlog.hpp"

class Email{
  public:
    Email():destinatarioId(0), id(0), msg(""){}
    Email(int dest, int v, std::string str):destinatarioId(dest), id(v), msg(str){}
    std::string getMensagem() const { return msg;};
    int getChave() const { return id; };
    int getDest() const { return destinatarioId; };
    void setMensagem(std::string const str){ msg = str;};
    void setChave(int const v){ id = v; };
    void setDest(int const v){  destinatarioId = v; };
    bool operator<(Email const &outro) const {return id < outro.getChave();};
    bool operator>(Email const &outro) const {return id > outro.getChave();};
    bool operator<=(Email const &outro) const {return id <= outro.getChave();};
    bool operator!=(Email const &outro) const {return (id != outro.getChave()) || (destinatarioId != outro.getDest());};
  private:
    int destinatarioId;
    int id;
    std::string msg;
};

#endif