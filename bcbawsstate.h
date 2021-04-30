/*
  File: bcbawsstate.h
  Kitchen Scale sketch
  Author: Brian C. Burnett
  GitHub repo: https://github.com/bcburnett/kitchenscale04252021
  Questions: https://github.com/bcburnett/kitchenscale04252021/discussions

  This application is in the Public Domain.
  All information is provided in good faith, however I make no representation
  or warranty of any kind, express or implied, regarding the accuracy, adequacy,
  validity, reliability, availability or completeness of this application.
*/

#pragma once
class BcbAwsState{
  public:
    // setter and getter for the uploading filename
    virtual String filename();
    virtual String filename(String value);
    
    virtual String command();
    virtual String command(String value);
    
    // should the browser reload the website
    virtual bool reload();
    virtual bool reload(bool value);

    // return a stringifyed json representation of the state
    virtual String getJSON();
};
