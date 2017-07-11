def get_relative(name)
    File.join(File.dirname(__FILE__), name)
end
$header = File.read(get_relative "header.h") + "\n"
$main_start = File.read(get_relative "startmain.h") + "\n"
$footer = File.read(get_relative "footer.h") + "\n"

$opts = {
    :has_math => false
}

$allowed_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz \n\t()0123456789,\\".chars
def transpile(prog)
    prog = prog.gsub(/λ/, "lambda ")
    invalid = prog.chars - $allowed_chars
    if invalid.size != 0
        $stderr.puts "Invalid character: #{invalid[0]}"
        exit -1
    end
    result = preheader = premain = ""
    prog.lines.each { |line|
        line.chomp!
        if line.lstrip.start_with? "import "
            line.slice! 0, 7 + line.index("import ")
            sections = line.split ","
            sections.each { |s|
                $opts[:has_math] = true if s == "math"
                preheader = "#include <#{s}.h>\n" + preheader
            }
            next
        elsif line.lstrip.start_with? "lambda "
            line.slice! 0, 7 + line.index("lambda ")
            name, *args, body = line.split(/,\s*/)
            premain += "#{name}(#{args * ","}){ return #{body}; }\n"
            next
        end
        if line.rstrip.end_with? "\\"
            result += line.rstrip[0..-2]
        else
            result += line
            result += ";\n"
        end
    }
    preheader + $header + premain + $main_start + result + $footer
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

flags = []
flags.push "-lm" if $opts[:has_math]

system("gcc #{flags.join " "} #{dest} -o #{outc}")
# p outc
system("./#{outc}")
# File.delete "#{outc}"
# File.delete "#{outc}.c"