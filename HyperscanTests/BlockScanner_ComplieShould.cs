using ABI.System;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using WinRT;

namespace Hyperscan.Tests
{
    [TestClass]
    public class BlockScanner_ComplieShould
    {
        private readonly BlockScanner _blockScanner = new BlockScanner();

        [TestMethod]
        public void ComplieSuccess()
        {
            try
            {
                _blockScanner.Compile("""++""", CompileFlags.Caseless | CompileFlags.UTF8 | CompileFlags.SOMLeftMost | CompileFlags.SOMLeftMost);
            }
            catch (System.Exception ex)
            {
                Assert.IsTrue(ex.Source == "WinRT.Runtime");
            }
        }
    }
}
