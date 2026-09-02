const fs = require("fs");
const path = require("path");

const gamma = Number(process.argv[2]);

if (!Number.isFinite(gamma) || gamma <= 0) {
    console.error("Usage: node tools/generate-gamma.js <gamma>");
    process.exit(1);
}

const values = Array.from({ length: 256 }, (_, i) =>
    Math.round(Math.pow(i / 255, gamma) * 255),
);

const rows = [];

for (let i = 0; i < values.length; i += 16) {
    rows.push(`    ${values.slice(i, i + 16).join(", ")},`);
}

const content = `#pragma once

#include <stdint.h>

// GENERATED GAMMA ${gamma}

constexpr uint8_t gammaTable[256] = {
${rows.join("\n")}
};
`;

const output = path.join(__dirname, "../include/gamma_table.h");

fs.writeFileSync(output, content);

console.log(`Generated gamma table with gamma = ${gamma}`);
