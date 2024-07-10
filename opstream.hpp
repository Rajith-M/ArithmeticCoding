//This file is used to create an output stream, which will be useful when we get a common prefix of bits that we can send rather than keeping it in memory
#ifndef OUTPUT_STREAM_HPP
#define OUTPUT_STREAM_HPP

class OutputBitStream:
public:    
    //Constructor | Input: An output stream | Initialises bitvec with 0, numbits with 0 and outfile to a jariable called output_stream
    OutputBitStream( std::ostream& output_stream ): bitvec {0}, numbits {0}, outfile {output_stream} { 
    }

    /*Destructor | Destructors are used when an object goes out of scope or is explicitly deleted. numbits keeps track of how many bits are currently in bitvec. 
    Any remaining bits are then output to the outputstream */
    ~OutputBitStream(){
        if (numbits > 0)
            output_byte();
    }

    void push_byte(u8 b){
        push_bits(b,8);
    }

     /*Writing some function overloading to handle cases when sending no or multiple bytes | We use parameter packs and templating here*/
    template<typename T, typename ...Ts>
    void push_bytes(T v1, Ts... rest){
        push_byte(v1);
        push_bytes(rest...);
    }

    /* Push a 32 bit unsigned integer value (LSB first) */
    void push_u32(u32 i){
        push_bits(i,32);
    }

    /* Push a 16 bit unsigned short value (LSB first) */
    void push_u16(u16 i){
        push_bits(i,16);
    }

    /* Push the lowest order num_bits bits from b into the stream
       with the least significant bit pushed first
    */
    void push_bits(u32 b, u32 num_bits){
        for (u32 i {0}; i < num_bits; i++)
            push_bit((b>>i)&1);
    }

    /* Push the lowest order num_bits bits from b into the stream
       with the least significant bit pushed first
    */
    void push_bits(u32 b, u32 num_bits){
        for (u32 i {0}; i < num_bits; i++)
            push_bit((b>>i)&1);
    }

    /* Push a single bit b (stored as the LSB of an unsigned int)
       into the stream */ 
    void push_bit(u32 b){
        bitvec |= (b&1)<<numbits;
        numbits++;
        if (numbits == 8)
            output_byte();
    }

    /* Flush the currently stored bits to the output stream */
    /* The value of fill_bit is used for any padding bits emitted. */
    void flush_to_byte(u32 fill_bit = 0){
        while(numbits != 0)
            push_bit(fill_bit);
    }


private:
    void output_byte(){
        outfile.put((unsigned char)bitvec);
        bitvec = 0;
        numbits = 0;
    }
    u32 bitvec;
    u32 numbits;
    std::ostream& outfile;
};


#endif 