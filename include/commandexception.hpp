#ifndef COMMANDEXCEPTION_HPP
#define COMMANDEXCEPTION_HPP

#include <exception>
#include <string>

enum CommandErrors
{
    SUCCES,
    EXECUTE_ERROR,
    PARAM_ERROR,
    RETURN_ERROR,
    FIND_ERROR,
    PERMISSION_ERROR
};

typedef CommandErrors CommandErrorTypes;

class CommandException : virtual public std::exception {
    protected:
        CommandErrorTypes error_number; ///< Error number
        int error_offset;               ///< Error offset
        std::string error_message;      ///< Error message
    
    public:
    /**
     * @brief Construct a new Command Exception object
     * 
     * @param msg a std::string that is the error message
     * @param err_num the error number
     * @param err_off the error number offset
     */
    explicit CommandException(const std::string &msg, CommandErrorTypes err_num, int err_off):
        error_number(err_num),
        error_offset(err_off),
        error_message(msg)
        {}

    /** Destructor.
     *  Virtual to allow for subclassing.
     */
    virtual ~CommandException() noexcept {}

    /** Returns a pointer to the (constant) error description.
     *  @return A pointer to a const char*. The underlying memory
     *  is in possession of the Except object. Callers must
     *  not attempt to free the memory.
     */
    virtual const char* what() const noexcept {
       return error_message.c_str();
    }
    
    /** Returns error number.
     *  @return #error_number
     */
    virtual CommandErrorTypes getErrorNumber() const noexcept {
        return error_number;
    }
    
    /**Returns error offset.
     * @return #error_offset
     */
    virtual int getErrorOffset() const noexcept {
        return error_offset;
    }
};

#endif // COMMANDEXCEPTION_HPP
