$header = File.read("header.h") + "\n"
$footer = File.read("footer.h") + "\n"

$allowed_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz \n\t()0123456789,\\".chars
def transpile(prog)
    invalid = prog.chars - $allowed_chars
    if invalid.size != 0
        $stderr.puts "Invalid character: #{invalid[0]}"
        exit -1
    end
    result = ""
    preheader = ""
    prog.lines.each { |line|
        line.chomp!
        if line.lstrip.start_with? "import "
            line.slice! 0, 7 + line.index("import ")
            preheader = "#include <#{line}.h>\n" + preheader
            next
        end
        if line.rstrip.end_with? "\\"
            result += line.rstrip[0..-2]
        else
            result += line
            result += ";\n"
        end
    }
    preheader + $header + result + $footer
end

def rm_extension(f)
    File.basename(f, File.extname(f))
end
file_name = ARGV[0]
file = File.read file_name
dest = ARGV[1] || rm_extension(file_name) + ".c"
outc = rm_extension(dest)

result = transpile file

File.write(dest, result)

system("gcc -w #{dest} -o #{outc}")
# p outc
system("./#{outc}")
# File.delete "#{outc}"
# File.delete "#{outc}.c"