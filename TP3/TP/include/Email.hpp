#ifndef EMAIL_H
#define EMAIL_H

#include <string>
// #include "msgassert.h"

class Email{
  public:
    Email():destinatarioId(0), id(0), msg(""){}
    Email(int dest, int v, std::string str):destinatarioId(dest), id(v), msg(str){}
    std::string getMensagem(){return msg;};
    int getChave() const {return id;};
    void setMensagem(std::string str){msg = str;};
    void setChave(int v){id = v;};
    bool operator<(Email const &outro) const {return id < outro.getChave();};
    bool operator<=(Email const &outro) const {return id <= outro.getChave();};
    bool operator!=(Email const &outro) const {return (id != outro.getChave()) || (destinatarioId != outro.destinatarioId);};
  private:
    int destinatarioId;
    int id;
    std::string msg;
};

#endif