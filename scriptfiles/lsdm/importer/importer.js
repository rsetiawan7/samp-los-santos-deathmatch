const fs = require('fs');
const readline = require('readline');
const sqlite3 = require('sqlite3').verbose();
const targetFiles = [
  'ls_airport.txt', 'ls_gen_inner.txt', 'ls_gen_outer.txt', 'ls_law.txt'
];

const db = new sqlite3.Database('../../vehicles.db');

// create instance of readline
// each instance is associated with single input stream

const files = fs.readdirSync(process.cwd());

const parseFile = file => {
  const rl = readline.createInterface({
    input: fs.createReadStream(file)
  });

  let line_no = 0;

  // event is emitted after each line
  rl.on('line', function(line) {
    line_no++;

    const value = String(line).split(',');

    db.run(`INSERT INTO los_santos (model,x,y,z,r,color1,color2) VALUES (?,?,?,?,?,?,?)`, value, function(err) {
      if (err) {
        console.error(err);
      }
    });
  });

  // end
  rl.on('close', function() {
    console.log(`Total lines (${file}) :  + ${line_no}`);
  });
};


for (const file of files) {
  if (targetFiles.includes(file)) {
    parseFile(file);
  }
}