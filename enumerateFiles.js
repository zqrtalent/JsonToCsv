const fs = require('fs')

var testDir = './src/third_party/rapidjson/include'

const listFiles = (dir) => {
    let files = fs.readdirSync(dir);
    (files || []).forEach(file => {
        if(fs.lstatSync(`${dir}/${file}`).isDirectory()){
            listFiles(`${dir}/${file}`)
        }
        else{
            if(dir.length > testDir.length)
                console.log(`"${dir.substr(testDir.length + 1)}/${file}",`)
            else
                console.log(`"${file}",`)
        }
    })
}

listFiles(testDir)